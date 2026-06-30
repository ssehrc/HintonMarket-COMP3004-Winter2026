#ifndef WAITLIST_H
#define WAITLIST_H

#pragma once 
#include <QString>
#include <queue>
using namespace std;

class Vendor;

class Waitlist{
    public:
        QString category;
        QString weekId;
        queue<Vendor*> vendorQueue;
        Waitlist(const QString& category, const QString& weekId) : category(category), weekId(weekId) {}

};
#endif // WAITLIST_H
