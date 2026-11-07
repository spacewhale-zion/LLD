#pragma once

#include <bits/stdc++.h>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\Enums\enums.cpp>
using namespace std;

class Vechile
{
private:
   string licensePlate;
   VechileType type;
   string ownerUserId;
public:
    Vechile(string lp, VechileType tp, string oui="GUEST")
        : licensePlate(move(lp)), type(tp), ownerUserId(move(oui)) {}

    string getLicensePlate() const {
        return licensePlate;
    }

    VechileType getType() const {
        return type;
    }

    string getOwnerUserId() const {
        return ownerUserId;
    }

    ~Vechile() = default;

};


