#ifndef WAITLISTSWINDOW_H
#define WAITLISTSWINDOW_H

#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QTableWidget>
#include "Vendor.h"
#include "WaitlistController.h"

class WaitlistsWindow : public QWidget {
    Q_OBJECT
    Vendor* vendor;
    WaitlistController* waitlistCtrl;
    QListWidget* waitlistsList;
    QTableWidget* table;
    void refreshWaitlists();
public:
    WaitlistsWindow(Vendor* vendor, WaitlistController* waitlistCtrl, QWidget* parent = nullptr);
private slots:
    void onLeaveWaitlistClicked();
};

#endif // WAITLISTSWINDOW_H
