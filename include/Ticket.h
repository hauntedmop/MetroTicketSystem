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
        Ticket(int id, std::vector<Station*> path, std::string name, std::string city);

        const int getId() const;
        const std::vector<Station*> getPath() const;
        const double getPrice() const;

        void printInfo() const;
        void printInstructions() const;

};