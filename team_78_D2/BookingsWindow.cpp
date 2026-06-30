#include "BookingsWindow.h"
#include <QHeaderView>
#include <QDebug>
#include <QShowEvent>

BookingsWindow::BookingsWindow(Vendor* vendor, MarketController* marketCtrl, QWidget* parent)
    : QWidget(parent), vendor(vendor), marketCtrl(marketCtrl)
{//UI for viewing and canceling bookings
    auto* layout = new QVBoxLayout(this);
    table = new QTableWidget(this);
    table->setColumnCount(2);

    QStringList headers;
    headers << "Date" << "Category";
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    layout->addWidget(table);

    auto* cancelButton = new QPushButton("Cancel Selected Booking", this);
    layout->addWidget(cancelButton);

    auto* closeButton = new QPushButton("Close", this);
    layout->addWidget(closeButton);

    setLayout(layout);
    refreshBookings();
    connect(cancelButton, &QPushButton::clicked, this, &BookingsWindow::onCancelBookingClicked);
    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
    resize(400, 300);
}

void BookingsWindow::refreshBookings() {
    vendor->bookings.clear();
    // Always reload from the database
    QSqlQuery query;
    query.prepare("SELECT m.date, b.category FROM Bookings b JOIN MarketSchedule m ON b.weekId = m.date WHERE b.vendorId = ?");
    query.addBindValue(vendor->id);
    if(query.exec()){
        while(query.next()){
            QString date = query.value(0).toString();
            QString category = query.value(1).toString();
            vendor->bookings.push_back(new Booking(vendor, new MarketDate(date)));
        }
    }else{
        qWarning() << "Failed to load bookings: " << query.lastError().text();
    }
    table->setRowCount((int)vendor->bookings.size());
    for (int i = 0; i < (int)vendor->bookings.size(); ++i) {
        Booking* b = vendor->bookings[i];
        table->setItem(i, 0, new QTableWidgetItem(b->marketDate->date));
        table->setItem(i, 1, new QTableWidgetItem(vendor->category));
    }
}

void BookingsWindow::onCancelBookingClicked() {
    int row = table->currentRow();
    if (row < 0 || row >= (int)vendor->bookings.size()) {
        QMessageBox::information(this, "Cancel", "Select a booking first.");
        return;
    }
    Booking* b = vendor->bookings[row];
    marketCtrl->cancelBooking(vendor, b);
    refreshBookings();
}

void BookingsWindow::showEvent(QShowEvent* event) {
    refreshBookings();
    QWidget::showEvent(event);
}
