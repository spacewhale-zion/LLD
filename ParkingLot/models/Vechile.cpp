#include <bits/stdc++.h>
#include<C:\ARYAN\STUDY\C++\LLD\ParkingLot\Enums\enums.cpp>
using namespace std;

class Vechile
{
private:
   string licensePlate;
   string type;
   string ownerUserId;
public:
    Vechile(string lp,string tp,string oui="GUEST"){
        this->licensePlate=lp;
        this->type=tp;
        this->ownerUserId=oui;
    };

    string getLicensePlate() const {
        return licensePlate;
    }

    VechileType getType() const {
        return type;
    }

    string getOwnerUserId() const {
        return ownerUserId;
    }

    ~Vechile();

};


