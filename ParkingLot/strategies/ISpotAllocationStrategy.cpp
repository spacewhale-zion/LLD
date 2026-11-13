#pragma once

#include <bits/stdc++.h>
#include "../models/ParkingSpot.cpp"
#include "../models/Vechile.cpp"
#include "../Enums/enums.cpp"
#include "../models/ParkingFloor.cpp"


using namespace std;

class ISpotAllocationStrategy{

    public:

    virtual shared_ptr<ParkingSpot> allocateSpot(
        const vector<shared_ptr<ParkingFloor>>& floors,
        const shared_ptr<Vehicle>& vehicle) = 0;

    virtual ~ISpotAllocationStrategy() = default;
};

class VipAwareAllocationStrategy : public ISpotAllocationStrategy{

    public:

    shared_ptr<ParkingSpot> allocateSpot(
        const vector<shared_ptr<ParkingFloor>>& floors,
        const shared_ptr<Vehicle>& vehicle) override{

        for (auto &floor:floors){

            for (auto &spot:floor->getSpots()){

                if (spot->isVipSpot() && spot->isReservedFor(vehicle->getOwnerUserId()) && spot->getSupportedType() == vehicle->getType()){
                    if(spot->tryPark(vehicle)){
                        return spot;
                    }
                }
            }
        }


        for (auto &floor:floors){

            for (auto &spot:floor->getSpots()){

                if (!spot->isVipSpot() && spot->getSupportedType() == vehicle->getType()){

                    if(spot->tryPark(vehicle)){
                        return spot;
                    }
                }
            }
        }

        return nullptr;
    }



};