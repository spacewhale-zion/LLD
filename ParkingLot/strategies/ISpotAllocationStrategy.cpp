#include <bits/stdc++.h>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\models\ParkingSpot.cpp>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\models\Vechile.cpp>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\Enums\enums.cpp>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\models\ParkingFloor.cpp>


using namespace std;

class ISpotAllocationStrategy{

    public:

    virtual shared_ptr<ParkingSpot> allocateSpot(
        const vector<shared_ptr<ParkingFloor>>& floors,
        const shared_ptr<Vechile>& vechile) = 0;

    virtual ~ISpotAllocationStrategy() = default;
};

class VipAwareAllocationStrategy : public ISpotAllocationStrategy{

    public:

    shared_ptr<ParkingSpot> allocateSpot(const vector<shared_ptr<ParkingFloor>>& floors,shared_ptr<Vechile>& vechile) override{

        for (auto &floor:floors){

            for (auto &spot:floor->getSpots()){

                if (spot->isVipSpot() && spot->isReservedFor(vechile->getOwnerUserId()) && spot->getSupportedType() == vechile->getType()){
                    if(spot->tryPark(vechile)){
                        return spot;
                    }
                }
            }
        }


        for (auto &floor:floors){

            for (auto &spot:floor->getSpots()){

                if (!spot->isVipSpot() && spot->getSupportedType() == vechile->getType() ){

                    if(spot->tryPark(vechile)){
                        return spot;
                    }
                }
            }
        }

        return nullptr;
    }



};