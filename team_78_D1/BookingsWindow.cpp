#include "BookingsWindow.h"
#include <QHeaderView>
#include <QDebug>

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
