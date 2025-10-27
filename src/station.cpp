#include "Station.h"

Station::Station(std::string cityName, std::vector<int> lineIds, std::vector<int> positions, std::string stationName)
    : city(cityName), lines(lineIds), linePositions(positions), name(stationName)
{

}

const std::vector<int>& Station::getLines() const{
    return lines;
}

const std::string Station::getName() const{
    return name;
}

const std::vector<Station*>& Station::getAdjacent() const{
    return adjacentStations;
}

void Station::addAdjacent(Station* neighbour){
    adjacentStations.push_back(neighbour);
}