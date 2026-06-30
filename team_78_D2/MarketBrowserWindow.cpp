#include "MarketBrowserWindow.h"
#include <QCloseEvent>
#include <QSqlQuery>

MarketBrowserWindow::MarketBrowserWindow(Repository* repo, MarketController* marketCtrl, WaitlistController* waitlistCtrl, Vendor* vendor, QWidget* parent)
    : QWidget(parent), repo(repo), marketCtrl(marketCtrl), waitlistCtrl(waitlistCtrl), vendor(vendor)
{
    //UI for browsing market dates and booking stalls
    auto* layout = new QVBoxLayout(this);
    table = new QTableWidget(this);
    table->setColumnCount(3);

    QStringList headers;
    headers << "Date" << "Food Slots" << "Artisan Slots";
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setRowCount((int)repo->marketDates.size());
    for (int i = 0; i < (int)repo->marketDates.size(); ++i) {
        auto date = repo->marketDates[i];
        // Query DB for booking counts
        QSqlQuery foodQuery;
        foodQuery.prepare("SELECT COUNT(*) FROM Bookings WHERE weekId = ? AND category = 'Food'");
        foodQuery.addBindValue(date->date);
        int foodCount = 0;
        if (foodQuery.exec() && foodQuery.next()) foodCount = foodQuery.value(0).toInt();
        QSqlQuery artisanQuery;
        artisanQuery.prepare("SELECT COUNT(*) FROM Bookings WHERE weekId = ? AND category = 'Artisan'");
        artisanQuery.addBindValue(date->date);
        int artisanCount = 0;
        if (artisanQuery.exec() && artisanQuery.next()) artisanCount = artisanQuery.value(0).toInt();
        table->setItem(i, 0, new QTableWidgetItem(date->date));
        table->setItem(i, 1, new QTableWidgetItem(QString("%1/%2").arg(foodCount).arg(date->foodCapacity)));
        table->setItem(i, 2, new QTableWidgetItem(QString("%1/%2").arg(artisanCount).arg(date->artisanCapacity)));
    }

    auto* bookButton = new QPushButton("Book Selected Date", this);
    auto* closeButton = new QPushButton("Close", this);

    layout->addWidget(table);
    layout->addWidget(bookButton);
    layout->addWidget(closeButton);

    connect(bookButton, &QPushButton::clicked, this, &MarketBrowserWindow::onBookClicked);
    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

    resize(500, 400);
    move(200, 150);   
}

void MarketBrowserWindow::onBookClicked() {
    int row = table->currentRow();
    if (row < 0 || row >= (int)repo->marketDates.size()) {
        QMessageBox::information(this, "Book", "Select a date first.");
        return;
    }
    MarketDate* date = repo->marketDates[row];

    // Check if vendor already has a booking
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM Bookings WHERE vendorId = ?");
    checkQuery.addBindValue(vendor->id);
    if (checkQuery.exec() && checkQuery.next()) {
        int count = checkQuery.value(0).toInt();
        if (count > 0) {
            QMessageBox::warning(this, "Error", "You can only have one booking at a time. Cancel your existing booking first.");
            return;
        }
    }

    Booking* booking = marketCtrl->bookStall(vendor, date);
    if (booking) { //Vendor may book if there is an available stall in their category
        QMessageBox::information(this, "Booked", "Stall booked successfully.");
        table->setItem(row, 1, new QTableWidgetItem(QString("%1/%2").arg(date->foodVendors.size()).arg(date->foodCapacity)));
        table->setItem(row, 2, new QTableWidgetItem(QString("%1/%2").arg(date->artisanVendors.size()).arg(date->artisanCapacity)));
        close();
    } else {//else will be prompted to join waitlist if they want to
        auto fullBookings = QMessageBox::question(this, "Full", "No stalls available for your category. Join waitlist?");
        if (fullBookings == QMessageBox::Yes) {
            waitlistCtrl->joinWaitlist(vendor, date);
            QMessageBox::information(this, "Waitlist", "You have been added to the waitlist.");
            close();
        }
    }
}

void MarketBrowserWindow::closeEvent(QCloseEvent* event) {
    if(parentWidget()){
        parentWidget()->show();
    }
    QWidget::closeEvent(event);
}
