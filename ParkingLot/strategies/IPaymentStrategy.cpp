#pragma once

#include <bits/stdc++.h>

using namespace std;

class IPaymentStrategy {
public:
    virtual bool processPayment(double amount) = 0;
    virtual ~IPaymentStrategy() = default;
};

class UpiPaymentStrategy : public IPaymentStrategy {
private:
    string upiId;

public:
    UpiPaymentStrategy(string id) : upiId(move(id)) {}

    bool processPayment(double amount) override {
        cout << "  [Payment] Successfully processed " << amount << " via UPI (" << upiId << ")\n";
        return true;
    }
};

class CardPaymentStrategy : public IPaymentStrategy {
private:
    string cardNumber;
    string cardHolderName;

public:
    CardPaymentStrategy(string number, string name) 
        : cardNumber(move(number)), cardHolderName(move(name)) {}

    bool processPayment(double amount) override {
        string lastFour = cardNumber.length() >= 4 ? cardNumber.substr(cardNumber.length() - 4) : cardNumber;
        cout << "  [Payment] Successfully processed " << amount << " via Card ending in " << lastFour << " (Cardholder: " << cardHolderName << ")\n";
        return true;
    }
};

class CashPaymentStrategy : public IPaymentStrategy {
public:
    bool processPayment(double amount) override {
        cout << "  [Payment] Successfully received " << amount << " in Cash at the Exit Booth\n";
        return true;
    }
};