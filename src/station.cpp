#include "Station.h"

Station::Station(std::string cityName, std::vector<int> lineIds, std::vector<int> positions, std::string stationName)
    : city(cityName), lines(lineIds), linePositions(positions), name(stationName)
{

}

const std::vector<int>& Station::getLines() const{
    return lines;
}