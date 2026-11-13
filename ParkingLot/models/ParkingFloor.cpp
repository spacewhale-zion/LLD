#pragma once

#include <bits/stdc++.h>
#include "ParkingSpot.cpp"
using namespace std;

class ParkingFloor
{
private:
    
    int floorNo;
public:
    explicit ParkingFloor(int fn):floorNo(fn) {}

    unordered_map<string,shared_ptr<ParkingSpot>>parkingSpotMap;

    void addSpot(const shared_ptr<ParkingSpot>& spot){
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



