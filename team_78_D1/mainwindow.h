#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "Repository.h"
#include "MarketController.h"
#include "WaitlistController.h"
#include "VendorDashboardWindow.h"

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

private:
    QLineEdit *nameEdit;
    QLabel *statusLabel;
    QPushButton *loginButton;
    Repository *repo;
    MarketController *marketCtrl;
    WaitlistController *waitlistCtrl;
};
#endif // MAINWINDOW_H
