#include "mainwindow.h"
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSqlQuery>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Enter username (vendor, operator, or admin name)");
    loginButton = new QPushButton("Login", this);
    statusLabel = new QLabel(this);
    statusLabel->setText("");

    layout->addWidget(nameEdit);
    layout->addWidget(loginButton);
    layout->addWidget(statusLabel);

    setCentralWidget(central);

    repo = new Repository();
    marketCtrl = new MarketController(repo);
    waitlistCtrl = new WaitlistController(repo);

    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginClicked);

    setWindowState(Qt::WindowMaximized); 
}

MainWindow::~MainWindow()
{
    delete repo;
    delete marketCtrl;
    delete waitlistCtrl;
}

void MainWindow::onLoginClicked()
{
    QString name = nameEdit->text().trimmed();
    Vendor* vendor = repo->findVendorName(name);

    if (!vendor) {
        statusLabel->setText("User not found.");
        return;
    }

    //Route based on user role/category
    if (vendor->category == "Operator") {
        // Open Market Operator Dashboard
        auto* opDash = new MarketOpDashboard(repo, marketCtrl, waitlistCtrl, vendor);
        connect(opDash, &MarketOpDashboard::logoutRequested, this, &MainWindow::onLogoutRequested);
        opDash->show();
        this->hide();
    } else if (vendor->category == "Food" || vendor->category == "Artisan") {
        //Open Vendor Dashboard
        auto* dash = new VendorDashboardWindow(repo, marketCtrl, waitlistCtrl, vendor);
        connect(dash, &VendorDashboardWindow::logoutRequested, this, &MainWindow::onLogoutRequested);
        dash->show();
        this->hide();
    } else {
        statusLabel->setText("Unknown user type.");
    }
}

void MainWindow::onLogoutRequested()
{
    this->show();
    nameEdit->clear();
    statusLabel->setText("");
}

//-------New function-------------
void MainWindow::showAllVendors()
{
    QSqlQuery query("SELECT * FROM Users WHERE role = 'Vendor'");
    qDebug()<<"All Vendors: ";
    while (query.next()) {
        QString name = query.value("name").toString();
        QString category = query.value("category").toString();
        qDebug() << "Name:" << name << ", Category:" << category;
    }
}