#include "MarketController.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Booking* MarketController::bookStall(Vendor* vendor, MarketDate* marketDate) {
    // Check slot count from database, not memory
    int currentCount = countBookingsForDate(marketDate->getDate(), vendor->category);
    int capacity = (vendor->category == "Food") ? marketDate->foodCapacity : marketDate->artisanCapacity;
    if(currentCount < capacity){
        // Insert booking into database
        QSqlQuery query;
        query.prepare("insert into Bookings(vendorId, weekId, category) values (?, ?, ?)");
        query.addBindValue(vendor->id);
        query.addBindValue(marketDate->getDate());
        query.addBindValue(vendor->category);
        if(!query.exec()){
            qWarning() << "Failed to insert booking into database:" << query.lastError().text();
            return nullptr;
        }
        // Reload bookings from database (UI should call refresh)
        return new Booking(vendor, marketDate);
    }
    return nullptr;
}

void MarketController::cancelBooking(Vendor* vendor, Booking* booking) {
    if(!vendor || !booking) return;
    // Remove booking from database
    QSqlQuery query;
    query.prepare("DELETE FROM Bookings WHERE vendorId = ? AND weekId = ? AND category = ?");
    query.addBindValue(vendor->id);
    query.addBindValue(booking->marketDate->date);
    query.addBindValue(vendor->category);
    if (!query.exec()) {
        qWarning() << "Failed to delete booking:" << query.lastError().text();
    }
    delete booking;
}

int MarketController::countBookingsForDate(const QString& date, const QString& category) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Bookings WHERE weekId = ? AND category = ?");
    query.addBindValue(date);
    query.addBindValue(category);
    if(query.exec() && query.next()) {
        return query.value(0).toInt();
    } else {
        qWarning() << "Failed to count bookings:" << query.lastError().text();
        return 0;
    }
}
