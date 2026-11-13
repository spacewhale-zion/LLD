#include<bits/stdc++.h>

using namespace std;

class URLMapper {

    private:
    string longUrl;
    string shortKey;
    long long createdAt;
    long long expiresAt;
    atomic<long long> clickCount;

    public:
    UrlMapping(string key, string url, long long ttlSeconds = 0)
        : shortKey(move(key)), longUrl(move(url)), clickCount(0) {
        createdAtEpoch = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
        expirationEpoch = (ttlSeconds > 0) ? (createdAtEpoch + ttlSeconds) : 0;
    }

    string getLongUrl() const {
        return longUrl;
    }
    string getShortKey() const {
        return shortKey;
    }

    long long getCreatedAt() const {
        return createdAt;
    }
    long long getExpiresAt() const {
        return expiresAt;
    }
    long long getClickCount() const {
        return clickCount.load();
    }

    bool isExpired() const {
        if (expiresAt == 0) return false;
        long long currentEpoch = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
        return currentEpoch > expiresAt;
    }

    void incrementClickCount() {
        clickCount++;
    }



};


