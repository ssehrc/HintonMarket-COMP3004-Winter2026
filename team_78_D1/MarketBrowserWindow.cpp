#include "MarketBrowserWindow.h"
#include <QCloseEvent>

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
//the market dates are listed with their current bookings depending on the vendor category  
    for (int i = 0; i < (int)repo->marketDates.size(); ++i) {
        auto date = repo->marketDates[i];
        table->setItem(i, 0, new QTableWidgetItem(date->date));
        table->setItem(i, 1, new QTableWidgetItem(QString("%1/%2").arg(date->foodVendors.size()).arg(date->foodCapacity)));
        table->setItem(i, 2, new QTableWidgetItem(QString("%1/%2").arg(date->artisanVendors.size()).arg(date->artisanCapacity)));
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
