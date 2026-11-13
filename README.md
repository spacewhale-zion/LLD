# Low-Level Design

This folder contains object-oriented low-level design exercises implemented in C++.

## Designs

### 1. Parking Lot

The first design in this repository is a parking-lot system. It demonstrates:

- Vehicle entry and exit through gates
- Floor and parking-spot management
- VIP-reserved spot allocation
- Ticket lifecycle management
- Pluggable pricing and payment strategies
- Thread-safe spot and ticket handling

Start here:

- [Parking Lot README](ParkingLot/README.md)
- [Parking Lot source](ParkingLot/main.cpp)
- [Parking Lot class diagram](ParkingLot/LLD%20Diagram.png)

## Build and Run

From the `ParkingLot` directory:

```powershell
g++ -std=c++17 -Wall -Wextra main.cpp -o parking_lot.exe
.\parking_lot.exe
```

Each design may have its own README with detailed architecture, design decisions, and execution instructions.
