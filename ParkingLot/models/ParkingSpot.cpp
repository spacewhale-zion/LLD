#include <bits/stdc++.h>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\models\Vechile.cpp>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\Enums\enums.cpp>

using namespace std;

class ParkingSpot{
    private:
    string spotId;
    string floorNo;
    VechileType supportedType;
    SpotStatus status;
    shared_ptr<Vechile>  parkedVechile;
    string reservedForUserId;
    mutable mutex spotMutex;
    public:
    ParkingSpot(string id, int floor, VechileType type, string vipUserId = "")
        : spotId(move(id)), floorNo(floor), supportedType(type),
          status(SpotStatus::AVAILABLE), reservedForUserId(move(vipUserId)),
          parkedVechile(nullptr) {}

    string getSpotId() const {
        return spotId;
    }

    int getFloorNumber() const {
        return floorNumber;
    }

    VechileType getSupportedType() const {
        return supportedType;
    }

    bool isVipSpot() const{
        return !reservedForUserId.empty();
    }
    bool isReservedFor(const string& userId) const {
        return !reservedForUserId.empty() && reservedForUserId == userId;
    }
    SpotStatus getStatus()const{
        lock_guard<mutex> lock(spotMutex);
        return status;
    }

    bool tryPark(const shared_ptr<Vechile>vechile){
        lock_guard<mutex> lock(spotMutex);

        if (status != SpotStatus::AVAILABLE ||  supportedType != vechile->getType()) return false;

        if (isVipSpot() && reservedForUserId != vechile->getOwnerUserId() )return false;

        status=SpotStatus::OCCUPIED;
        parkedVechile=vechile;
        return true;
    }

    void vacate(){
        lock_guard<mutex> lock(spotMutex);
        parkedVechile=nullptr;
        status=SpotStatus::AVAILABLE;
    }
};