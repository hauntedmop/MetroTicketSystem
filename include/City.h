#pragma once

#include <vector>
#include <string>
#include "Station.h"
#include "MetroLine.h"

class City{
    private:
        std::string name;
        std::vector<Station> stations;
        std::vector<MetroLine> lines;
        int basePrice;

    public:
        City(std::string name);
        void loadStationsFromCSV(const std::string& fileName);
        void loadLinesFromCSV(const std::string& fileName);
        void printStations();
        void buildAdjacency();

};