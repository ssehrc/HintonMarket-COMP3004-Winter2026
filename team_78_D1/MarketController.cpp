#include "MarketController.h"

Booking* MarketController::bookStall(Vendor* vendor, MarketDate* marketDate) {
    if(vendor->category == "Food"){
        if((int)marketDate->foodVendors.size() < marketDate->foodCapacity){
            marketDate->foodVendors.push_back(vendor);
            Booking* booking = new Booking(vendor, marketDate);
            vendor->bookings.push_back(booking);
            return booking;
        }
    }else if(vendor->category == "Artisan"){
        if((int)marketDate->artisanVendors.size() < marketDate->artisanCapacity){
            marketDate->artisanVendors.push_back(vendor);
            Booking* booking = new Booking(vendor, marketDate);
            vendor->bookings.push_back(booking);
            return booking;
        }
    }
    return nullptr;
}

void MarketController::cancelBooking(Vendor* vendor, Booking* booking) {
    if(!vendor || !booking) return;
    //Remove booking from vendor's list. They are stored as pointers so the exact one can be selected to be removed
    auto& vector = vendor->bookings;
    vector.erase(remove(vector.begin(), vector.end(), booking), vector.end());

    auto date = booking->marketDate;
    if(vendor->category == "Food"){
        auto& foodVendors = date->foodVendors;
        foodVendors.erase(remove(foodVendors.begin(), foodVendors.end(), vendor), foodVendors.end());
    }else if(vendor->category == "Artisan"){
        auto& artisanVendors = date->artisanVendors;
        artisanVendors.erase(remove(artisanVendors.begin(), artisanVendors.end(), vendor), artisanVendors.end());
    }
    
    delete booking;
}
