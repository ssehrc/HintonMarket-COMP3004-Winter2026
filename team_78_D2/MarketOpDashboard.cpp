#include "MarketOpDashboard.h"
#include <QHeaderView>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QHBoxLayout>
#include <QGroupBox>

MarketOpDashboard::MarketOpDashboard(Repository* repo, MarketController* marketCtrl, WaitlistController* waitlistCtrl, Vendor* operatorUser, QWidget* parent)
    : QWidget(parent), repo(repo), marketCtrl(marketCtrl), waitlistCtrl(waitlistCtrl), operatorUser(operatorUser)
{
    auto* mainLayout = new QVBoxLayout(this);

    auto* titleLabel = new QLabel(QString("Market Operator Dashboard - %1").arg(operatorUser->name), this);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
    mainLayout->addWidget(titleLabel);

    //allows market operator to book stalls on behalf of vendors
    auto* bookGroupBox = new QGroupBox("Book a Stall for Vendor", this);
    auto* bookLayout = new QHBoxLayout(bookGroupBox);

    vendorComboBox = new QComboBox(this);
    dateComboBox = new QComboBox(this);

    //adding vendors to coombo box
    for (auto v : repo->vendors) {
        if (v->category == "Food" || v->category == "Artisan") {
            vendorComboBox->addItem(QString("%1 (%2)").arg(v->name).arg(v->category), v->id);
        }
    }
    //adding market dates to combo box
    for (auto d : repo->marketDates) {
        dateComboBox->addItem(d->date, d->date);
    }

    auto* bookButton = new QPushButton("Book Stall", this);
    connect(bookButton, &QPushButton::clicked, this, &MarketOpDashboard::onBookStallClicked);

    bookLayout->addWidget(new QLabel("Vendor:"));
    bookLayout->addWidget(vendorComboBox);
    bookLayout->addWidget(new QLabel("Date:"));
    bookLayout->addWidget(dateComboBox);
    bookLayout->addWidget(bookButton);
    mainLayout->addWidget(bookGroupBox);

    //Bookings
    auto* bookingsLabel = new QLabel("Current Bookings", this);
    bookingsLabel->setStyleSheet("font-weight: bold;");
    mainLayout->addWidget(bookingsLabel);

    bookingsTable = new QTableWidget(this);
    bookingsTable->setColumnCount(4);
    QStringList bookingHeaders;
    bookingHeaders << "Vendor" << "Category" << "Date" << "Action";
    bookingsTable->setHorizontalHeaderLabels(bookingHeaders);
    bookingsTable->horizontalHeader()->setStretchLastSection(true);
    mainLayout->addWidget(bookingsTable);

    auto* cancelBookingButton = new QPushButton("Cancel Selected Booking", this);
    connect(cancelBookingButton, &QPushButton::clicked, this, &MarketOpDashboard::onCancelBookingClicked);
    mainLayout->addWidget(cancelBookingButton);

    //Waitlists
    auto* waitlistsLabel = new QLabel("Vendor Waitlists", this);
    waitlistsLabel->setStyleSheet("font-weight: bold;");
    mainLayout->addWidget(waitlistsLabel);

    waitlistsTable = new QTableWidget(this);
    waitlistsTable->setColumnCount(4);
    QStringList waitlistHeaders;
    waitlistHeaders << "Vendor" << "Category" << "Week" << "Action";
    waitlistsTable->setHorizontalHeaderLabels(waitlistHeaders);
    waitlistsTable->horizontalHeader()->setStretchLastSection(true);
    mainLayout->addWidget(waitlistsTable);

    auto* removeWaitlistButton = new QPushButton("Remove from Waitlist", this);
    connect(removeWaitlistButton, &QPushButton::clicked, this, &MarketOpDashboard::onRemoveFromWaitlistClicked);
    mainLayout->addWidget(removeWaitlistButton);

    //Logout button
    auto* logoutButton = new QPushButton("Logout", this);
    connect(logoutButton, &QPushButton::clicked, this, &MarketOpDashboard::logout);
    mainLayout->addWidget(logoutButton);

    setLayout(mainLayout);
    resize(900, 700);

    refreshBookings();
    refreshWaitlists();
}

void MarketOpDashboard::refreshBookings() {
    //Clear table
    bookingsTable->setRowCount(0);
    
    //Query database for all bookings with vendor info
    QSqlQuery query;
    query.prepare("SELECT b.id, u.name, u.category, b.weekId FROM Bookings b JOIN Users u ON b.vendorId = u.id ORDER BY b.weekId");
    
    if (!query.exec()) {
        qWarning() << "Failed to query bookings:" << query.lastError().text();
        return;
    }
    
    int row = 0;
    while (query.next()) {
        bookingsTable->insertRow(row);
        
        int bookingId = query.value(0).toInt();
        QString vendorName = query.value(1).toString();
        QString vendorCategory = query.value(2).toString();
        QString date = query.value(3).toString();
        
        bookingsTable->setItem(row, 0, new QTableWidgetItem(vendorName));
        bookingsTable->setItem(row, 1, new QTableWidgetItem(vendorCategory));
        bookingsTable->setItem(row, 2, new QTableWidgetItem(date));
        bookingsTable->setItem(row, 3, new QTableWidgetItem(QString::number(bookingId)));
        
        row++;
    }
}

void MarketOpDashboard::refreshWaitlists() {
    //Clear table
    waitlistsTable->setRowCount(0);
    
    //Query database for all waitlist entries with vendor info
    QSqlQuery query;
    query.prepare("SELECT w.id, u.name, u.category, w.weekId FROM Waitlist w JOIN Users u ON w.vendorId = u.id ORDER BY w.weekId, w.id");
    
    if (!query.exec()) {
        qWarning() << "Failed to query waitlists:" << query.lastError().text();
        return;
    }
    
    int row = 0;
    while (query.next()) {
        waitlistsTable->insertRow(row);
        
        int waitlistId = query.value(0).toInt();
        QString vendorName = query.value(1).toString();
        QString vendorCategory = query.value(2).toString();
        QString weekId = query.value(3).toString();
        
        waitlistsTable->setItem(row, 0, new QTableWidgetItem(vendorName));
        waitlistsTable->setItem(row, 1, new QTableWidgetItem(vendorCategory));
        waitlistsTable->setItem(row, 2, new QTableWidgetItem(weekId));
        waitlistsTable->setItem(row, 3, new QTableWidgetItem(QString::number(waitlistId)));
        
        row++;
    }
}

void MarketOpDashboard::onBookStallClicked() {
    int vendorId = vendorComboBox->currentData().toInt();
    QString date = dateComboBox->currentData().toString();

    //get vendor
    Vendor* vendor = nullptr;
    for (auto v : repo->vendors) {
        if (v->id == vendorId) {
            vendor = v;
            break;
        }
    }

    if (!vendor) {
        QMessageBox::warning(this, "Error", "Vendor not found.");
        return;
    }

    //get market date
    MarketDate* marketDate = repo->getDateIndex(date);
    if (!marketDate) {
        QMessageBox::warning(this, "Error", "Market date not found.");
        return;
    }

    // Check if vendor already has a booking for any date
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM Bookings WHERE vendorId = ?");
    checkQuery.addBindValue(vendor->id);
    if (checkQuery.exec() && checkQuery.next()) {
        int count = checkQuery.value(0).toInt();
        if (count > 0) {
            QMessageBox::warning(this, "Error", "Vendor can only have one booking at a time.");
            return;
        }
    }

    //Book the stall
    Booking* booking = marketCtrl->bookStall(vendor, marketDate);
    if (booking) {
        QMessageBox::information(this, "Success", QString("Booked stall for %1 on %2").arg(vendor->name).arg(date));
        refreshBookings();
        delete booking;
    } else {
        QMessageBox::warning(this, "Error", "Failed to book stall. No available slots for this category.");
    }
}

void MarketOpDashboard::onCancelBookingClicked() {
    int row = bookingsTable->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Error", "Please select a booking to cancel.");
        return;
    }

    QString vendorName = bookingsTable->item(row, 0)->text();
    QString date = bookingsTable->item(row, 2)->text();

    //Find vendor
    Vendor* vendor = nullptr;
    for (auto v : repo->vendors) {
        if (v->name == vendorName) {
            vendor = v;
            break;
        }
    }

    if (!vendor) {
        QMessageBox::warning(this, "Error", "Vendor not found.");
        return;
    }

    //Will delete booking from database
    QSqlQuery query;
    query.prepare("DELETE FROM Bookings WHERE vendorId = ? AND weekId = ?");
    query.addBindValue(vendor->id);
    query.addBindValue(date);
    if (query.exec()) {
        QMessageBox::information(this, "Success", QString("Cancelled booking for %1 on %2").arg(vendor->name).arg(date));
        refreshBookings();
    } else {
        QMessageBox::warning(this, "Error", "Failed to cancel booking.");
    }
}

void MarketOpDashboard::onRemoveFromWaitlistClicked() {
    int row = waitlistsTable->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Error", "Please select a waitlist entry to remove.");
        return;
    }

    QString vendorName = waitlistsTable->item(row, 0)->text();
    QString weekId = waitlistsTable->item(row, 2)->text();

    //Find vendor
    Vendor* vendor = nullptr;
    for (auto v : repo->vendors) {
        if (v->name == vendorName) {
            vendor = v;
            break;
        }
    }

    if (!vendor) {
        QMessageBox::warning(this, "Error", "Vendor not found.");
        return;
    }

    //Remove from database
    QSqlQuery query;
    query.prepare("DELETE FROM Waitlist WHERE vendorId = ? AND weekId = ?");
    query.addBindValue(vendor->id);
    query.addBindValue(weekId);
    if (query.exec()) {
        QMessageBox::information(this, "Success", QString("Removed %1 from waitlist").arg(vendor->name));
        refreshWaitlists();
    } else {
        QMessageBox::warning(this, "Error", "Failed to remove from waitlist.");
    }
}

void MarketOpDashboard::logout() {
    this->close();
    emit logoutRequested();
}