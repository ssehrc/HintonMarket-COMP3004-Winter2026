#ifndef MARKETOPDASHBOARD_H
#define MARKETOPDASHBOARD_H

#pragma once
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QMessageBox>
#include "Repository.h"
#include "MarketController.h"
#include "WaitlistController.h"
#include "Vendor.h"

class MarketOpDashboard : public QWidget {

    Q_OBJECT
    
    private:
        Repository* repo;
        MarketController* marketCtrl;
        WaitlistController* waitlistCtrl;
        Vendor* operatorUser;

        QTableWidget* vendorTable;
        QTableWidget* bookingsTable;
        QTableWidget* waitlistsTable;
        QComboBox* dateComboBox;
        QComboBox* vendorComboBox;

        void refreshVendors();
        void refreshBookings();
        void refreshWaitlists();

    public:
        MarketOpDashboard(Repository* repo, MarketController* marketCtrl, WaitlistController* waitlistCtrl, Vendor* operatorUser, QWidget* parent = nullptr);

    signals:
        void logoutRequested();

    public slots:
        void logout();

    private slots:
        void onBookStallClicked();
        void onCancelBookingClicked();
        void onRemoveFromWaitlistClicked();
};

#endif // MARKETOPDASHBOARD_H