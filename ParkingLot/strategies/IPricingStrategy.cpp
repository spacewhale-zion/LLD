#pragma once

#include <bits/stdc++.h>

#include "../Enums/enums.cpp"
#include "../models/Ticket.cpp"

using namespace std;

class IPricingStrategy{
    public:

    virtual double calculateFare(const shared_ptr<Ticket>& ticket, long exitHour) = 0;
    virtual ~IPricingStrategy() = default;
};


class HourlyPricingStrategy:public IPricingStrategy{
    private:
    unordered_map<VechileType,double> hourlyRates;
    
    public:

    HourlyPricingStrategy() {
        hourlyRates[VechileType::TWO_WHEELER] = 20.0;
        hourlyRates[VechileType::FOUR_WHEELER] = 50.0;
        hourlyRates[VechileType::HEAVY] = 100.0;
    }
    


    double calculateFare(const shared_ptr<Ticket>& ticket, long exitHour) override {
          
        if (ticket->getAllocatedSpot()->isReservedFor(ticket->getVehicle()->getOwnerUserId())) {
            return 0.0;
        }

        long long hoursParked = max(1L, exitHour - ticket->getEntryTime());
        double rate = hourlyRates.at(ticket->getVehicle()->getType());
        
        return hoursParked * rate;

    }
};