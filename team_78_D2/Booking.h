#ifndef BOOKING_H
#define BOOKING_H

#pragma once 
class Vendor;
class MarketDate;

class Booking{
    public:
        Vendor* vendor;
        MarketDate* marketDate;
        Booking(Vendor* vendor, MarketDate* marketDate) : vendor(vendor), marketDate(marketDate) {}
};
#endif // BOOKING_H
