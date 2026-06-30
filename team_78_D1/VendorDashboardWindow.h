#ifndef VENDORDASHBOARDWINDOW_H
#define VENDORDASHBOARDWINDOW_H

#pragma once
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "Repository.h"
#include "MarketController.h"
#include "WaitlistController.h"
#include "Vendor.h"
#include "BookingsWindow.h"
#include "WaitlistsWindow.h"
#include <QDebug>
class MarketBrowserWindow;

class VendorDashboardWindow : public QWidget {
    Q_OBJECT
    private:
        Repository* repo;
        MarketController* marketCtrl;
        WaitlistController* waitlistCtrl;
        Vendor* vendor;

        QLabel* infoLabel;
        BookingsWindow* bookingsWin = nullptr;
        WaitlistsWindow* waitlistsWin = nullptr;

        void refresh();

    public:
        VendorDashboardWindow(Repository* repo, MarketController* marketCtrl, WaitlistController* waitlistCtrl, Vendor* vendor, QWidget* parent = nullptr);

    
};


#endif // VENDORDASHBOARDWINDOW_H
