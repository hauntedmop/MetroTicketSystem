# Metro Ticket System

A C++ console program that simulates a metro ticketing system for multiple cities. Users can view stations, buy tickets, and get route instructions.

## Features
Load cities, lines, and stations from CSV files

Find shortest paths (BFS)

Ticket pricing by city and distance

Save/load tickets with unique IDs

Menu: Buy Ticket, View Tickets, See Stations, Quit

Build & Run
```
rm -rf build
mkdir build && cd build
cmake ..
make
./metro.exe
```
Notes

Transfers between lines are supported.

CSV files define city, station, and line data.

Project is a work in progress; all functionality built but could be improved
