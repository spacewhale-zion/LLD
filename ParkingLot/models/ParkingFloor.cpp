#pragma once

#include <bits/stdc++.h>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\models\ParkingSpot.cpp>
using namespace std;

class ParkingFloor
{
private:
    
  string floorNo;
public:
    ParkingFloor(string fn):floorNo(fn){};

    unordered_map<string,shared_ptr<ParkingSpot>>parkingSpotMap;

    void addSpot(shared_ptr<ParkingSpot>&spot){
        if(spot){
            parkingSpotMap[spot->getSpotId()]=spot;
        }
    }
    vector<shared_ptr<ParkingSpot>> getSpots(){

        vector<shared_ptr<ParkingSpot>>allSpots;

        for (const auto &pair:parkingSpotMap){
            allSpots.push_back(pair.second);
        }
        return allSpots;
    }
    ~ParkingFloor() = default;

};



