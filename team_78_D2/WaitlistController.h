#ifndef WAITLISTCONTROLLER_H
#define WAITLISTCONTROLLER_H

#pragma once
#include "Repository.h"
#include "MarketDate.h"
#include "Vendor.h"

class WaitlistController{
    public:
        Repository* repo;
        WaitlistController(Repository* repo) : repo(repo) {}

        QString weekIdForDate(MarketDate* marketDate); //Week number out of four weeks

        void joinWaitlist(Vendor* vendor, MarketDate* marketDate);
        void leaveWaitlist(Vendor* vendor, const QString& key);
};
#endif // WAITLISTCONTROLLER_H
