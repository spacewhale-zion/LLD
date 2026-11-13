#pragma once

#include <bits/stdc++.h>
#include "Vechile.cpp"
#include "../Enums/enums.cpp"

using namespace std;

class ParkingSpot{
    private:
    string spotId;
    int floorNumber;
    VehicleType supportedType;
    SpotStatus status;
    shared_ptr<Vehicle> parkedVehicle;
    string reservedForUserId;
    mutable ParkingMutex spotMutex;
    public:
    ParkingSpot(string id, int floor, VehicleType type, string vipUserId = "")
        : spotId(move(id)), floorNumber(floor), supportedType(type),
                    status(SpotStatus::AVAILABLE), parkedVehicle(nullptr),
                    reservedForUserId(move(vipUserId)) {}

    string getSpotId() const {
        return spotId;
    }

    int getFloorNumber() const {
        return floorNumber;
    }

    VehicleType getSupportedType() const {
        return supportedType;
    }

    bool isVipSpot() const{
        return !reservedForUserId.empty();
    }
    bool isReservedFor(const string& userId) const {
        return !reservedForUserId.empty() && reservedForUserId == userId;
    }
    SpotStatus getStatus()const{
        std::lock_guard<ParkingMutex> lock(spotMutex);
        return status;
    }

    bool tryPark(const shared_ptr<Vehicle>& vehicle){
        std::lock_guard<ParkingMutex> lock(spotMutex);

        if (!vehicle || status != SpotStatus::AVAILABLE || supportedType != vehicle->getType()) return false;

        if (isVipSpot() && reservedForUserId != vehicle->getOwnerUserId()) return false;

        status=SpotStatus::OCCUPIED;
        parkedVehicle=vehicle;
        return true;
    }

    void vacate(){
        std::lock_guard<ParkingMutex> lock(spotMutex);
        parkedVehicle=nullptr;
        status=SpotStatus::AVAILABLE;
    }
};