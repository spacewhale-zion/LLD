#pragma once

#include <bits/stdc++.h>
#include "ParkingSpot.cpp"
#include "Vechile.cpp"
#include "../Enums/enums.cpp"

using namespace std;

class Ticket{

    private:
    string ticketId;
    string entryGateId;
    long entryTime;
    long exitTime;
    shared_ptr<Vehicle> vehicle;
    shared_ptr<ParkingSpot>allocatedSpot;
    TicketStatus status;

    public:

    Ticket(string id,string gateId,shared_ptr<Vehicle> v,shared_ptr<ParkingSpot> ap,long time)
    : ticketId(move(id)),entryGateId(move(gateId)),entryTime(time),exitTime(0),vehicle(move(v)),allocatedSpot(move(ap)),status(TicketStatus::ACTIVE){}



    string getTicketId() const {
        return ticketId;
    }

    string getEntryGateId() const {
        return entryGateId;
    }

    shared_ptr<Vehicle> getVechile() const {
        return vehicle;
    }

    shared_ptr<Vehicle> getVehicle() const {
        return vehicle;
    }

    shared_ptr<ParkingSpot> getAllocatedSpot() const {
        return allocatedSpot;
    }

    long  getEntryTime() const {
        return entryTime;
    }

    long  getExitTime() const {
        return exitTime;
    }

    TicketStatus getStatus() const {
        return status;
    }

    void markPaid(long long time){
        exitTime=time;
        status=TicketStatus::PAID;
    }

};