#pragma once

#include <bits/stdc++.h>
#include "../Enums/enums.cpp"
using namespace std;

class Vehicle
{
private:
   string licensePlate;
   VechileType type;
   string ownerUserId;
public:
    Vehicle(string lp, VehicleType tp, string oui="GUEST")
        : licensePlate(move(lp)), type(tp), ownerUserId(move(oui)) {}

    string getLicensePlate() const {
        return licensePlate;
    }

    VehicleType getType() const {
        return type;
    }

    string getOwnerUserId() const {
        return ownerUserId;
    }

    ~Vehicle() = default;

};

using Vechile = Vehicle;


