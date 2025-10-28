#include "MetroLine.h"
#include "Station.h"
#include <string>
#include <vector>

MetroLine::MetroLine(int lineNumber, std::string colour, std::vector<Station*> lineStations, std::string cityName)
    : lineId(lineNumber), name(colour), stations(lineStations), city(cityName)
{

};

const std::vector<Station*>& MetroLine::getStations() const{
    return stations;
}

const int MetroLine::getLineID() const{
    return lineId;
}