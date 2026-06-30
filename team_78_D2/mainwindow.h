#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "MarketController.h"
#include "WaitlistController.h"
#include "VendorDashboardWindow.h"
#include "MarketOpDashboard.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginClicked();
    void showAllVendors();
    void onLogoutRequested();

private:
    Repository *repo;
    QLineEdit *nameEdit;
    QLabel *statusLabel;
    QPushButton *loginButton;
    MarketController *marketCtrl;
    WaitlistController *waitlistCtrl;
};
#endif // MAINWINDOW_H
