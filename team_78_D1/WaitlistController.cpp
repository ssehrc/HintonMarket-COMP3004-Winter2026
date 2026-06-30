#include "WaitlistController.h"

QString WaitlistController::weekIdForDate(MarketDate* marketDate){
    int index = 0;
    for(int i = 0; i < (int)repo->marketDates.size(); ++i){
        if(repo->marketDates[i] == marketDate){
            index = i;
            break;
        }
    }
    return QString("Week%1").arg(index + 1);
}

void WaitlistController::joinWaitlist(Vendor* vendor, MarketDate* marketDate){
    QString weekId = weekIdForDate(marketDate);
    Waitlist* waitlist = repo->getWaitlist(vendor->category, weekId);
    if(!waitlist) {
        waitlist = new Waitlist(vendor->category, weekId);
        repo->waitlists.push_back(waitlist);
    }
    waitlist->vendorQueue.push(vendor);
    vendor->waitlists.push_back(vendor->category + "-" + weekId);
}
void WaitlistController::leaveWaitlist(Vendor* vendor, const QString& key){
    auto& waitlist = vendor->waitlists;
    waitlist.erase(remove(waitlist.begin(), waitlist.end(), key), waitlist.end());
}