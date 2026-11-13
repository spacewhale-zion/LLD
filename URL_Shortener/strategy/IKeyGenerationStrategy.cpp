#include<bits/stdc++.h>

using namespace std;


class IKeyGenerationStrategy {
public:
    virtual string generateKey() = 0;
    virtual ~IKeyGenerationStrategy() = default;
};


class Base62KeyGenerationStrategy : public IKeyGenerationStrategy {

    private:
    atomic<long long>Counter;
    string base62Chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    public:
    Base62KeyGenerationStrategy() : Counter(0) {}

    string generateKey() override {
        long long currentCounter = Counter++;
        string key;

        do {
            key += base62Chars[currentCounter % 62];
            currentCounter /= 62;
        } while (currentCounter > 0);

        reverse(key.begin(), key.end());
        return key;
    } b
}