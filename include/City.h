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
        double basePrice = 30;
        double stationPrice = 10;

    public:
        City(std::string name, double basePrice, double stationPrice);

        static City loadCityFromCSV(const std::string& fileName, const std::string& cityName);
        void loadStationsFromCSV(const std::string& fileName);
        void loadLinesFromCSV(const std::string& fileName);
        void printStations();
        void buildAdjacency();

        const double getBasePrice() const;
        const double getStationPrice() const;
        const std::string getName() const;
        Station* getStationByName(const std::string& name);

};