#include <bits/stdc++.h>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\models\ParkingSpot.cpp>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\models\Vechile.cpp>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\Enums\enums.cpp>

using namespace std;

class Ticket{

    private:
    string ticketId;
    string entryGateId;
    long entryTime;
    long exitTime;
    shared_ptr<Vechile>vechile;
    shared_ptr<ParkingSpot>allocatedSpot;
    TicketStatus status;

    public:

    Ticket(string id,string gateId,shared_ptr<Vechile>v,shared_ptr<ParkingSpot>ap,long time)
    : ticketId(move(id)),entryGateId(move(gateId)),vechile(move(v)),allocatedSpot(ap),entryTime(time),exitTime(0),status(TicketStatus::ACTIVE){}



    string getTicketId(){
        return ticketId;
    }

    string getEntryGateId(){
        return entryGateId;
    }

    shared_ptr<Vechile> getVechile() const {
        return vechile;
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