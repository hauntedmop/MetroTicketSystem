#include "Station.h"
#include <algorithm>

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

const std::vector<Edge>& Station::getAdjacent() const{
    return edgeMap;
}

void Station::addEdge(Station* neighbour, int lineNum){
    if(std::find(edgeMap.begin(), edgeMap.end(), Edge{neighbour, lineNum}) == edgeMap.end())
        edgeMap.push_back({neighbour, lineNum});
}

int Station::getLinePosition(int lineNumber) const {
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i] == lineNumber) {
            return linePositions[i];
        }
    }
    return -1;
}