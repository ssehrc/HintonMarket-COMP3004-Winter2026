#include "VendorDashboardWindow.h"
#include "MarketBrowserWindow.h"

VendorDashboardWindow::VendorDashboardWindow(Repository* repo, MarketController* m, WaitlistController* w, Vendor* v, QWidget* parent)
    : QWidget(parent), repo(repo), marketCtrl(m), waitlistCtrl(w), vendor(v)
{
    auto* mainLayout = new QVBoxLayout(this);

    infoLabel = new QLabel(this);
    mainLayout->addWidget(infoLabel);

    auto* browseButton = new QPushButton("Browse Market Dates", this);
    auto* viewBookingsButton = new QPushButton("View Bookings", this);
    auto* viewWaitlistsButton = new QPushButton("View Waitlists", this);
    auto* logoutButton = new QPushButton("Logout", this);

    mainLayout->addWidget(browseButton);
    mainLayout->addWidget(viewBookingsButton);
    mainLayout->addWidget(viewWaitlistsButton);
    mainLayout->addWidget(logoutButton);

    connect(browseButton, &QPushButton::clicked, this, [this]() {
        auto* browser = new MarketBrowserWindow(this->repo, this->marketCtrl, this->waitlistCtrl, this->vendor, this);
        browser->show();
    });

    connect(viewBookingsButton, &QPushButton::clicked, this, [this]() {
        if (!this->bookingsWin) {
            this->bookingsWin = new BookingsWindow(this->vendor, this->marketCtrl, this);
            connect(this->bookingsWin, &QObject::destroyed, this, [this]() { this->bookingsWin = nullptr; });
        }
        this->bookingsWin->show();
        this->bookingsWin->raise();
        this->bookingsWin->activateWindow();
    });
    
    connect(viewWaitlistsButton, &QPushButton::clicked, this, [this]() {
        if (!this->waitlistsWin) {
            this->waitlistsWin = new WaitlistsWindow(this->vendor, this->waitlistCtrl, this);
            connect(this->waitlistsWin, &QObject::destroyed, this, [this]() { this->waitlistsWin = nullptr; });
        }
        this->waitlistsWin->show();
        this->waitlistsWin->raise();
        this->waitlistsWin->activateWindow();
    });

    connect(logoutButton, &QPushButton::clicked, this, &VendorDashboardWindow::logout);

    refresh();
}

void VendorDashboardWindow::refresh() {
    QString info = QString("Vendor: %1 (%2)\n"
        "Owner: %3\n"
        "Address: %4\n"
        "Email: %5\n"
        "Phone: %6\n"
        "License #: %7 (exp: %8)\n"
        "Policy: %9 (exp: %10)")
        .arg(vendor->name)
        .arg(vendor->category)
        .arg(vendor->ownerName)
        .arg(vendor->address)
        .arg(vendor->email)
        .arg(vendor->phone)
        .arg(vendor->licenseNumber)
        .arg(vendor->licenseExpiry)
        .arg(vendor->policyDetails)
        .arg(vendor->policyExpiry);
    infoLabel->setText(info);
}

void VendorDashboardWindow::logout() {
    this->close();
    emit logoutRequested();
}
