#include <bits/stdc++.h>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\models\ParkingSpot.cpp>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\models\Vechile.cpp>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\Enums\enums.cpp>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\models\ParkingFloor.cpp>

#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\strategies\ISpotAllocationStrategy.cpp>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\strategies\IPricingStrategy.cpp>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\strategies\IPaymentStrategy.cpp>


using namespace std;


class ParkingLotService{

    private:
    vector<shared_ptr<ParkingFloor>> floors;

    unordered_map<string,Ticket> activeTickets;

    ISpotAllocationStrategy allocationStrategy;
    IPricingStrategy pricingStrategy;

    mutex ticketMutex;     // Lock for thread-safe access to activeTickets map
    mutex consoleMutex;    // Lock to keep multi-threaded console logs readable
    atomic<int> ticketCounter{100}; // Thread-safe atomic counter for unique ticket IDs

    public:

    ParkingLotService(shared_ptr<ISpotAllocationStrategy> alloc,
                      shared_ptr<IPricingStrategy> pricing)
        : allocationStrategy(move(alloc)), pricingStrategy(move(pricing)) {}

    void addFloor(shared_ptr<ParkingFloor>&floor){
        floors.push_back(floor);
    }

    void setPricingStrategy(IPricingStrategy &ps){
        this->pricingStrategy=ps;
    }

    shared_ptr<Ticket>issueTicket(const string&gateId, const shared_ptr<Vechile>&v,long entryHour){
        auto spot= allocationStrategy->allocateSpot(floors,v);

        if (!spot){
            lock_guard<mutex>loglock(consoleMutex);
            lock_guard<mutex> logLock(consoleMutex);
            cout << "[Gate " << gateId << " - DENIED] No available spot for Vehicle "
                 << vehicle->getLicensePlate() << " (User: " << vehicle->getOwnerUserId() << ")\n";
            return nullptr;
        }
        string ticketId="TKT-"+to_string(++ticketCounter);

        auto ticket= make_shared<Ticket>(ticketId,gateId,v,spot,entryHour);

        {
            lock_guard<mutex>lock(ticketMutex);
            activeTickets[ticketId]=ticket;
        }

        // 4. Log successful entry
        {
            lock_guard<mutex> logLock(consoleMutex);
            cout << "[Gate " << gateId << " - ENTRY] Vehicle " << vehicle->getLicensePlate()
                 << " allocated Spot " << spot->getSpotId()
                 << (spot->isVipSpot() ? " [VIP RESERVED]" : " [PUBLIC]")
                 << " on Floor " << spot->getFloorNumber()
                 << " | Ticket: " << ticketId << "\n";
        }
        
        return ticket;


    }

    double processExit(const string &exitGateId,const string &ticketId,IPaymentStrategy & paymentMethod ,long exitHour ){
        shared_ptr<Ticket>ticket;
        
        {
            lock_guard<mutex>lock(ticketMutex);
            auto it=activeTickets[ticketId];

            if (it == activeTickets.end()) {
                throw invalid_argument("Invalid or already closed Ticket ID: " + ticketId);
            }

            ticket=it->second;
            activeTickets.erase(it);
        }

        double fee= pricingStrategy->calculateFee(ticket,exitHour);
        {
            lock_guard<mutex> logLock(consoleMutex);
            cout << "[Gate " << exitGateId << " - EXIT] Processing Ticket " << ticketId
                 << " for Vehicle " << ticket->getVehicle()->getLicensePlate() << "\n";

            if (fee > 0.0) {
                if (!paymentMethod.processPayment(fee)) {
                    throw runtime_error("Payment failed!");
                }
            } else {
                cout << "  [Payment] ₹0 (VIP Permanently Booked Spot - Prepaid)\n";
            }

            ticket->markPaid(exitHour);
            ticket->getAllocatedSpot()->vacate();
            
            cout << "  [Spot Freed] Spot " << ticket->getAllocatedSpot()->getSpotId() << " is now AVAILABLE.\n";
        }
        
        return fee;


    }


};