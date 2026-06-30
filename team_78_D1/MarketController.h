#ifndef MARKETCONTROLLER_H
#define MARKETCONTROLLER_H

#pragma once
#include "Repository.h"
#include "Booking.h"
#include <algorithm>

using namespace std;

class MarketController{
    public: 
        Repository* repo;

        MarketController(Repository* repo) : repo(repo) {}

        Booking* bookStall(Vendor* vendor, MarketDate* marketDate);
        void cancelBooking(Vendor* vendor, Booking* booking);
};

#endif // MARKETCONTROLLER_H
