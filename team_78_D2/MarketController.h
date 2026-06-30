#ifndef MARKETCONTROLLER_H
#define MARKETCONTROLLER_H

#pragma once
#include <iostream>
#include "Repository.h"
#include "Booking.h"
#include <algorithm>
#include <QSqlQuery>

using namespace std;

class MarketController{
    public: 
        Repository* repo;

        MarketController(Repository* repo) : repo(repo) {}

        Booking* bookStall(Vendor* vendor, MarketDate* marketDate);
        void cancelBooking(Vendor* vendor, Booking* booking);
        int countBookingsForDate(const QString& date, const QString& category);
};

#endif // MARKETCONTROLLER_H
