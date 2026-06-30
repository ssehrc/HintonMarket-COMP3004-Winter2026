#ifndef BOOKINGSWINDOW_H
#define BOOKINGSWINDOW_H

#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QTableWidget>
#include "Vendor.h"
#include "MarketController.h"

class BookingsWindow : public QWidget {
    Q_OBJECT
    Vendor* vendor;
    MarketController* marketCtrl;
    QListWidget* bookingsList;
    QTableWidget* table;
    void refreshBookings();
public:
    BookingsWindow(Vendor* vendor, MarketController* marketCtrl, QWidget* parent = nullptr);
private slots:
    void onCancelBookingClicked();
};

#endif // BOOKINGSWINDOW_H
