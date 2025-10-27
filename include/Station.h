#pragma once

#include <vector>
#include <string>

class Station{
    private:
        std::vector<int> linePositions;
        std::vector<int> lines;
        std::string city;
        std::string name;
        std::vector<Station*> adjacentStations;

    public:
        Station(std::string cityName, std::vector<int> lineIds, std::vector<int> positions, std::string stationName);

        Station(const Station&) = default;
        Station& operator=(const Station&) = default;
        Station(Station&&) = default;
        Station& operator=(Station&&) = default;

        const std::vector<int>& getLines() const;
        const std::string getName() const;
        const std::vector<Station*>& getAdjacent() const;

        void addAdjacent(Station* neighbour);

};