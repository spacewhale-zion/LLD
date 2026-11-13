#include <bits/stdc++.h>
#include "../models/Ticket.cpp"
#include "../models/Vechile.cpp"
#include "ParkingLotService.cpp"
#include "../strategies/IPaymentStrategy.cpp"

using namespace std;

class Gate{
    private:
    string gateId;
    shared_ptr<ParkingLotService> parkingLotService;

    public:

    Gate(string id, shared_ptr<ParkingLotService> pls):gateId(move(id)),parkingLotService(move(pls)) {}

    string getGateId() const {
        return gateId;
    }

    shared_ptr<ParkingLotService> getParkingLotService() const {
        return parkingLotService;
    }

};

class EntryGate : public Gate {
    public:
    EntryGate(string id, shared_ptr<ParkingLotService> pls) : Gate(move(id), move(pls)) {}

    shared_ptr<Ticket> allowEntry(const shared_ptr<Vehicle>& vehicle, long entryHour) {
        return getParkingLotService()->issueTicket(getGateId(), vehicle, entryHour);
    }


};

class ExitGate : public Gate {
    public:
    ExitGate(string id, shared_ptr<ParkingLotService> pls) : Gate(move(id), move(pls)) {}

    double allowExit(const string& ticketId, long exitHour, IPaymentStrategy& paymentMethod) {
        return getParkingLotService()->processExit(getGateId(), ticketId, paymentMethod, exitHour);
    }
};
