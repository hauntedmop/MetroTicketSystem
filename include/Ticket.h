#pragma once

#include <vector>
#include <string>
#include "Station.h"
#include "City.h"

class Ticket{
    private:
        int ticketID;
        double price;
        std::string passengerName;
        std::vector<Station*> stationPath;
        std::string cityName;
        City* city;
        void calculatePrice();

    public:
        Ticket(int id, std::vector<Station*> path, std::string name, City* city);

        const int getId() const;
        const std::vector<Station*> getPath() const;
        const double getPrice() const;
        const std::string getPassengerName() const;

        void printInfo() const;
        void printInstructions() const;

};