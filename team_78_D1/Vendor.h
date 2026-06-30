#ifndef VENDOR_H
#define VENDOR_H

#pragma once

#include <QString>
#include <vector>

class Booking;

using namespace std;

class Vendor{
    public:
        QString name; // Business name
        QString category; // Food or Artisan or Operator or Admin
        QString ownerName;
        QString address;
        QString email;
        QString phone;
        QString licenseNumber;
        QString licenseExpiry;
        QString policyDetails;
        QString policyExpiry;

        vector<Booking*> bookings;
        vector<QString> waitlists;
        Vendor(const QString& name, const QString& category, const QString& ownerName, const QString& address, const QString& email, const QString& phone, const QString& licenseNumber, const QString& licenseExpiry, const QString& policyDetails, const QString& policyExpiry)
            : name(name), category(category), ownerName(ownerName), address(address), email(email), phone(phone), licenseNumber(licenseNumber), licenseExpiry(licenseExpiry), policyDetails(policyDetails), policyExpiry(policyExpiry) {}
};

#endif // VENDOR_H
