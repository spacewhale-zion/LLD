#include <bits/stdc++.h>

#include "Enums/enums.cpp"
#include "models/Vechile.cpp"
#include "models/ParkingSpot.cpp"
#include "models/ParkingFloor.cpp"
#include "strategies/ISpotAllocationStrategy.cpp"
#include "strategies/IPricingStrategy.cpp"
#include "strategies/IPaymentStrategy.cpp"
#include "services/ParkingLotService.cpp"
#include "services/Gate.cpp"

using namespace std;

int main() {
    auto allocStrategy = make_shared<VipAwareAllocationStrategy>();
    auto priceStrategy = make_shared<HourlyPricingStrategy>();

    auto parkingService = make_shared<ParkingLotService>(allocStrategy, priceStrategy);

    auto floor1 = make_shared<ParkingFloor>(1);
    
    floor1->addSpot(make_shared<ParkingSpot>("F1-VIP1", 1, VehicleType::FOUR_WHEELER, "USER_VIP_ARYAN"));
    
    floor1->addSpot(make_shared<ParkingSpot>("F1-PUB1", 1, VehicleType::FOUR_WHEELER));
    floor1->addSpot(make_shared<ParkingSpot>("F1-BIKE1", 1, VehicleType::TWO_WHEELER));
    
    parkingService->addFloor(floor1);

    EntryGate entryGate1("ENTRY-1", parkingService);
    EntryGate entryGate2("ENTRY-2", parkingService);
    ExitGate exitGate1("EXIT-1", parkingService);

    cout << "=== SCENARIO 1: Entry Allocation at 2 Gates ===\n";
    auto regCar1 = make_shared<Vehicle>("KA-01-1111", VehicleType::FOUR_WHEELER, "USER_REG_1");
    auto regCar2 = make_shared<Vehicle>("MH-02-2222", VehicleType::FOUR_WHEELER, "USER_REG_2");

    shared_ptr<Ticket> tktReg1, tktReg2;
    
    tktReg1 = entryGate1.allowEntry(regCar1, 10);
    tktReg2 = entryGate2.allowEntry(regCar2, 10);

    cout << "\n=== SCENARIO 2: VIP User Arrives & Parks in Permanently Booked Spot ===\n";
    auto vipCar = make_shared<Vehicle>("DL-01-VIP-0001", VehicleType::FOUR_WHEELER, "USER_VIP_ARYAN");
    auto vipTicket = entryGate1.allowEntry(vipCar, 11);

    cout << "\n=== SCENARIO 3: Regular Car & VIP Car Exit ===\n";
    UpiPaymentStrategy upi("aryan@upi");
    CashPaymentStrategy cash;

    shared_ptr<Ticket> activeRegularTicket = tktReg1 ? tktReg1 : tktReg2;
    if (activeRegularTicket) {
        exitGate1.allowExit(activeRegularTicket->getTicketId(), 13, upi);
    }

    if (vipTicket) {
        exitGate1.allowExit(vipTicket->getTicketId(), 15, cash);
    }

    return 0;
}