#include "Repository.h"


Repository::Repository(){
    // Clear all vectors to avoid stale data
    for(auto v : vendors) delete v;
    for(auto d : marketDates) delete d;
    for(auto w : waitlists) delete w;
    vendors.clear();
    marketDates.clear();
    waitlists.clear();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("marketplace.db");
    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
        return;
    }
    // Load market dates
    QSqlQuery dateQuery("SELECT * FROM MarketSchedule");
    while (dateQuery.next()) {
        QString date = dateQuery.value("date").toString();
        int foodCapacity = dateQuery.value("foodCapacity").toInt();
        int artisanCapacity = dateQuery.value("artisanCapacity").toInt();
        MarketDate* marketDate = new MarketDate(date);
        marketDate->foodCapacity = foodCapacity;
        marketDate->artisanCapacity = artisanCapacity;
        marketDates.push_back(marketDate);
    }
    // Load vendors (including operator and admin)
    QSqlQuery vendorQuery("SELECT * FROM Users");
    while (vendorQuery.next()) {
        int id = vendorQuery.value("id").toInt();
        QString name = vendorQuery.value("name").toString();
        QString category = vendorQuery.value("category").toString();
        QString ownerName = vendorQuery.value("ownerName").toString();
        QString address = vendorQuery.value("address").toString();
        QString email = vendorQuery.value("email").toString();
        QString phone = vendorQuery.value("phone").toString();
        QString licenseNumber = vendorQuery.value("licenseNumber").toString();
        QString licenseExpiry = vendorQuery.value("licenseExpiryDate").toString();
        QString policyDetails = vendorQuery.value("policyDetails").toString();
        QString policyExpiry = vendorQuery.value("policyExpiryDate").toString();
        Vendor* vendor = new Vendor(id, name, category, ownerName, address, email, phone, licenseNumber, licenseExpiry, policyDetails, policyExpiry);
        vendors.push_back(vendor);
    }
    // Load waitlists from DB (fix table name)
    QSqlQuery waitlistQuery("SELECT * FROM Waitlist");
    while (waitlistQuery.next()) {
        QString category = waitlistQuery.value("category").toString();
        QString weekId = waitlistQuery.value("weekId").toString();
        int vendorId = waitlistQuery.value("vendorId").toInt();
        Vendor* vendor = nullptr;
        for (auto v : vendors) {
            if (v->id == vendorId) {
                vendor = v;
                break;
            }
        }
        Waitlist* waitlist = getWaitlist(category, weekId);
        if (!waitlist) {
            waitlist = new Waitlist(category, weekId);
            waitlists.push_back(waitlist);
        }
        if (vendor) {
            waitlist->vendorQueue.push(vendor);
            vendor->waitlists.push_back(category + "-" + weekId);
        }
    }
}
Repository::~Repository(){
    for(auto v : vendors) delete v;
    for(auto d : marketDates) delete d;
    for(auto w : waitlists) delete w;
}

Vendor* Repository::findVendorName(const QString& name){
    for(auto v : vendors){
        if(v->name == name){
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
