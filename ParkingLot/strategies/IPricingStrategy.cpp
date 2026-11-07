#include <bits/stdc++.h>

#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\Enums\enums.cpp>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\models\Ticket.cpp>

using namespace std;

class IPricingStrategy{
    public:

    virtual double calculateFare(shared_ptr<Ticket>& ticket,long exit) = 0;
};


class HourlyPricingStrategy:public IPricingStrategy{
    private:
    unordered_map<VechileType,double> hourlyRates;
    
    public:

    HourlyPricingStrategy() {
        hourlyRates[VehicleType::TWO_WHEELER] = 20.0; 
        hourlyRates[VehicleType::FOUR_WHEELER] = 50.0; 
        hourlyRates[VehicleType::HEAVY] = 100.0;   
    }
    


    double (shared_ptr<Ticket> ticket,long exit){
          
        if (ticket->getAllocatedSpot()->isReservedFor(ticket->getVehicle()->getOwnerUserId())) {
            return 0.0;
        }

        // Calculate hours parked (minimum 1 hour charged)
        long long hoursParked = max(1LL, exitTime - ticket->getEntryTime());
        
        // Fetch rate based on vehicle type
        double rate = hourlyRates[ticket->getVehicle()->getType()];
        
        return hoursParked * rate

    }
}