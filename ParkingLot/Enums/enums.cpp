#pragma once

#include <atomic>

class ParkingMutex {
private:
    std::atomic_flag locked = ATOMIC_FLAG_INIT;

public:
    void lock() {
        while (locked.test_and_set(std::memory_order_acquire)) {
        }
    }

    void unlock() {
        locked.clear(std::memory_order_release);
    }
};

enum class VehicleType {
    TWO_WHEELER,
    FOUR_WHEELER,
    HEAVY
};

using VechileType = VehicleType;

enum class SpotStatus {
    AVAILABLE,
    OCCUPIED,
    UNDER_MAINTENANCE
};

enum class TicketStatus {
    ACTIVE,
    PAID
};
