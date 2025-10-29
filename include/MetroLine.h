#pragma once

#include <string>
#include <vector>
#include "Station.h"

class MetroLine{
    private:
        int lineId;
        std::string name;
        std::vector<Station*> stations;
        std::string city;

    public:
        MetroLine(int lineNumber, std::string colour, std::vector<Station*> lineStations, std::string cityName);
        const std::vector<Station*>& getStations() const;
        const int getLineID() const;
        const std::string getName() const;
};