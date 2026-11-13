#pragma once

#include <bits/stdc++.h>
#include "../models/ParkingSpot.cpp"
#include "../models/Vechile.cpp"
#include "../Enums/enums.cpp"
#include "../models/ParkingFloor.cpp"
#include "../models/Ticket.cpp"
#include "../strategies/ISpotAllocationStrategy.cpp"
#include "../strategies/IPricingStrategy.cpp"
#include "../strategies/IPaymentStrategy.cpp"


using namespace std;


class ParkingLotService{

    private:
    vector<shared_ptr<ParkingFloor>> floors;

    unordered_map<string,shared_ptr<Ticket>> activeTickets;

    shared_ptr<ISpotAllocationStrategy> allocationStrategy;
    shared_ptr<IPricingStrategy> pricingStrategy;

    ParkingMutex ticketMutex;
    ParkingMutex consoleMutex;
    atomic<int> ticketCounter{100};

    public:

    ParkingLotService(shared_ptr<ISpotAllocationStrategy> alloc,
                      shared_ptr<IPricingStrategy> pricing)
        : allocationStrategy(move(alloc)), pricingStrategy(move(pricing)) {}

    void addFloor(const shared_ptr<ParkingFloor>& floor){
        floors.push_back(floor);
    }

    void setPricingStrategy(shared_ptr<IPricingStrategy> ps){
        pricingStrategy = move(ps);
    }

    shared_ptr<Ticket> issueTicket(const string& gateId, const shared_ptr<Vehicle>& vehicle, long entryHour){
        if (!vehicle) {
            throw invalid_argument("Vehicle cannot be null");
        }
        auto spot = allocationStrategy->allocateSpot(floors, vehicle);

        if (!spot){
            std::lock_guard<ParkingMutex> logLock(consoleMutex);
            cout << "[Gate " << gateId << " - DENIED] No available spot for Vehicle "
                  << vehicle->getLicensePlate() << " (User: " << vehicle->getOwnerUserId() << ")\n";
            return nullptr;
        }
        string ticketId="TKT-"+to_string(++ticketCounter);

        auto ticket = make_shared<Ticket>(ticketId, gateId, vehicle, spot, entryHour);

        {
            std::lock_guard<ParkingMutex> lock(ticketMutex);
            activeTickets[ticketId]=ticket;
        }

        {
            std::lock_guard<ParkingMutex> logLock(consoleMutex);
            cout << "[Gate " << gateId << " - ENTRY] Vehicle " << vehicle->getLicensePlate()
                 << " allocated Spot " << spot->getSpotId()
                 << (spot->isVipSpot() ? " [VIP RESERVED]" : " [PUBLIC]")
                 << " on Floor " << spot->getFloorNumber()
                 << " | Ticket: " << ticketId << "\n";
        }
        
        return ticket;


    }

    double processExit(const string& exitGateId, const string& ticketId, IPaymentStrategy& paymentMethod, long exitHour) {
        shared_ptr<Ticket>ticket;

        std::lock_guard<ParkingMutex> ticketLock(ticketMutex);
        auto it = activeTickets.find(ticketId);
        if (it == activeTickets.end()) {
            throw invalid_argument("Invalid or already closed Ticket ID: " + ticketId);
        }

        ticket = it->second;

        if (exitHour < ticket->getEntryTime()) {
            throw invalid_argument("Exit time cannot be before entry time");
        }

        double fee = pricingStrategy->calculateFare(ticket, exitHour);
        {
            std::lock_guard<ParkingMutex> logLock(consoleMutex);
            cout << "[Gate " << exitGateId << " - EXIT] Processing Ticket " << ticketId
                 << " for Vehicle " << ticket->getVehicle()->getLicensePlate() << "\n";

            if (fee > 0.0) {
                if (!paymentMethod.processPayment(fee)) {
                    throw runtime_error("Payment failed!");
                }
            } else {
                cout << "  [Payment] 0 (VIP permanently booked spot - prepaid)\n";
            }

            ticket->markPaid(exitHour);
            ticket->getAllocatedSpot()->vacate();

            cout << "  [Spot Freed] Spot " << ticket->getAllocatedSpot()->getSpotId() << " is now AVAILABLE.\n";
        }

        activeTickets.erase(it);
        return fee;


    }


};