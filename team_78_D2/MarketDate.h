#ifndef MARKETDATE_H
#define MARKETDATE_H

#pragma once
#include <QString>
#include <vector>
using namespace std;
#include <QDebug>
class Vendor;

class MarketDate{
    public:
        QString date; // Ex: 2026-03-12
        //The capacity of bookings for the market date for each vendor category
        int foodCapacity;
        int artisanCapacity;

        vector<Vendor*> foodVendors;
        vector<Vendor*> artisanVendors;
        MarketDate(const QString& date) : date(date), foodCapacity(2), artisanCapacity(2) {}
        QString getDate()const {return date;}
};

#endif // MARKETDATE_H
