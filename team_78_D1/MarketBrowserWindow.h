#ifndef MARKETBROWSERWINDOW_H
#define MARKETBROWSERWINDOW_H

#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include "Repository.h"
#include "MarketController.h"
#include "WaitlistController.h"
#include "Vendor.h"

class MarketBrowserWindow : public QWidget {
    Q_OBJECT
    private:
        Repository* repo;
        MarketController* marketCtrl;
        WaitlistController* waitlistCtrl;
        Vendor* vendor;

        QTableWidget* table;

    public:
        MarketBrowserWindow(Repository* repo, MarketController* marketCtrl, WaitlistController* waitlistCtrl, Vendor* vendor, QWidget* parent = nullptr);

    protected:
        void closeEvent(QCloseEvent* event) override;

    private slots:
        void onBookClicked();
};

#endif // MARKETBROWSERWINDOW_H
