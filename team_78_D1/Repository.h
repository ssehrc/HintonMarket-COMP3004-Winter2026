#ifndef REPOSITORY_H
#define REPOSITORY_H

#pragma once
#include <QDate>
#include "Vendor.h"
#include "MarketDate.h"
#include "Waitlist.h"
using namespace std;

class Repository{
    public:
        vector<Vendor*> vendors;
        vector<MarketDate*> marketDates;
        vector<Waitlist*> waitlists;
        Repository();
        ~Repository();

        Vendor* findVendorName(const QString& name);
        MarketDate* getDateIndex(const QString& dateIndex);
        Waitlist* getWaitlist(const QString& category, const QString& weekId);
};

#endif // REPOSITORY_H
