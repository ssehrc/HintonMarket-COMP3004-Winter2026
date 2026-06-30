#include "mainwindow.h"
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create widgets
    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText("Enter username");
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

    setWindowState(Qt::WindowMaximized); // Open main window maximized
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
        statusLabel->setText("Vendor not found.");
        return;
    }

    auto* dash = new VendorDashboardWindow(repo, marketCtrl, waitlistCtrl, vendor);
    dash->show();
    this->hide();
}
