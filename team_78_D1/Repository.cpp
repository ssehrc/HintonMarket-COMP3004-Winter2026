#include "Repository.h"

Repository::Repository(){
    QDate start(2026, 3, 1);
    for(int i = 0; i < 4; ++i){
        QDate date = start.addDays(i*7);
        marketDates.push_back(new MarketDate(date.toString("yyyy-MM-dd")));
    }

    // 4 food vendors
    vendors.push_back(new Vendor("John Doe", "Food", "John Doe", "123 Main St", "john@example.com", "555-1234", "F-123", "2027-01-01", "FoodPolicyA", "2027-01-01"));
    vendors.push_back(new Vendor("Sue Smith", "Food", "Sue Smith", "456 Oak Ave", "sue@example.com", "555-5678", "F-456", "2027-02-01", "FoodPolicyB", "2027-02-01"));
    vendors.push_back(new Vendor("Joe Bloggs", "Food", "Joe Bloggs", "789 Pine Rd", "joe@example.com", "555-9012", "F-789", "2027-03-01", "FoodPolicyC", "2027-03-01"));
    vendors.push_back(new Vendor("Ruth Brown", "Food", "Ruth Brown", "321 Maple St", "ruth@example.com", "555-3456", "F-321", "2027-04-01", "FoodPolicyD", "2027-04-01"));

    // 4 artisan vendors
    vendors.push_back(new Vendor("Sally Johnson", "Artisan", "Sally Johnson", "654 Cedar Ave", "sally@example.com", "555-7890", "A-654", "2027-05-01", "ArtisanPolicyA", "2027-05-01"));
    vendors.push_back(new Vendor("Tom Brown", "Artisan", "Tom Brown", "987 Spruce Rd", "tom@example.com", "555-2345", "A-987", "2027-06-01", "ArtisanPolicyB", "2027-06-01"));
    vendors.push_back(new Vendor("Emily Davis", "Artisan", "Emily Davis", "159 Elm St", "emily@example.com", "555-6789", "A-159", "2027-07-01", "ArtisanPolicyC", "2027-07-01"));
    vendors.push_back(new Vendor("Michael Wilson", "Artisan", "Michael Wilson", "753 Birch Rd", "michael@example.com", "555-4321", "A-753", "2027-08-01", "ArtisanPolicyD", "2027-08-01"));

    // Market operator and system admin
    vendors.push_back(new Vendor("Market Operator", "Operator", "Op Name", "1 Market St", "operator@example.com", "555-0001", "O-001", "2028-01-01", "OpPolicy", "2028-01-01"));
    vendors.push_back(new Vendor("System Admin", "Admin", "Admin Name", "2 Admin Ave", "admin@example.com", "555-0002", "S-002", "2028-02-01", "AdminPolicy", "2028-02-01"));
}
Repository::~Repository(){
    for(auto v : vendors) delete v;
    for(auto d : marketDates) delete d;
    for(auto w : waitlists) delete w;
}

Vendor* Repository::findVendorName(const QString& name){
    for(auto v : vendors){
        if(v->name == name && (v->category == "Food" || v->category == "Artisan")){
            return v;
        }
    }
    return nullptr;
}

MarketDate* Repository::getDateIndex(const QString& dateIndex){
    for(auto d : marketDates){
        if(d->getDate() == dateIndex) {
            return d;
        }
    }
    return nullptr;
}
Waitlist* Repository::getWaitlist(const QString& category, const QString& weekId){
    for(auto w : waitlists){
        if(w->category == category && w->weekId == weekId){
            return w;
        }
    }
    return nullptr;
}
