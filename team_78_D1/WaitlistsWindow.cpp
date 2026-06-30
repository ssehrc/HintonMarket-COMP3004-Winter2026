#include "WaitlistsWindow.h"
#include <QHeaderView>
#include <QDebug>

WaitlistsWindow::WaitlistsWindow(Vendor* vendor, WaitlistController* waitlistCtrl, QWidget* parent)
    : QWidget(parent), vendor(vendor), waitlistCtrl(waitlistCtrl)
{
    auto* layout = new QVBoxLayout(this);
    table = new QTableWidget(this);
    table->setColumnCount(1);

    QStringList headers;
    headers << "Waitlist Key";
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    layout->addWidget(table);

    auto* leaveButton = new QPushButton("Leave Selected Waitlist", this);
    layout->addWidget(leaveButton);

    auto* closeButton = new QPushButton("Close", this);
    layout->addWidget(closeButton);
    setLayout(layout);
    refreshWaitlists();

    connect(leaveButton, &QPushButton::clicked, this, &WaitlistsWindow::onLeaveWaitlistClicked);
    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

    resize(400, 300);
}

void WaitlistsWindow::refreshWaitlists() {
    table->clearContents();
    table->setRowCount((int)vendor->waitlists.size());
    
    QStringList headers;
    headers << "Waitlist Key";
    table->setHorizontalHeaderLabels(headers);
    for (int i = 0; i < (int)vendor->waitlists.size(); ++i) {
        table->setItem(i, 0, new QTableWidgetItem(vendor->waitlists[i]));
    }
}

void WaitlistsWindow::onLeaveWaitlistClicked() {
    int row = table->currentRow();
    if (row < 0 || row >= (int)vendor->waitlists.size()) {
        QMessageBox::information(this, "Leave", "Select a waitlist first.");
        return;
    }
    QString key = vendor->waitlists[row];
    waitlistCtrl->leaveWaitlist(vendor, key);
    refreshWaitlists();
}
