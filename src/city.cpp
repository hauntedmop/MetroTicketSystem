#include "City.h"
#include "Station.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

City::City(std::string cityName, double basePrice, double stationPrice)
    : name(cityName), basePrice(basePrice), stationPrice(stationPrice)
{

};

void City::loadStationsFromCSV(const std::string& fileName){
    std::ifstream file(fileName);
    if(!file.is_open())
        throw std::runtime_error("No CSV file opened");
    
    std::string line;
    while(std::getline(file, line)){
        if(line.empty()) continue;

        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while(std::getline(ss, cell, ','))
            row.push_back(cell);

        if(row.size() < 4) continue;
        if((row.size() - 2)%2 != 0) continue;
        std::string cityName = row[0];
        if(cityName != name) continue;
        std::string stationName = row[1];
        std::vector<int> lineIds;
        std::vector<int> positions;
        for (size_t i = 2; i < row.size(); i++) {
            if (i % 2 == 0)
                lineIds.push_back(stoi(row[i]));
            else
                positions.push_back(stoi(row[i]));
        }
        Station station = Station(cityName, lineIds, positions, stationName);
        stations.push_back(station);
    }
    file.close();
}

void City::loadLinesFromCSV(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open())
        throw std::runtime_error("No CSV file opened");

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(ss, cell, ','))
            row.push_back(cell);

        std::string cityName = row[0];
        if (cityName != name) continue;

        int lineNumber = stoi(row[1]);
        std::string colour = row[2];
        std::vector<Station*> lineStations;

        for (Station& station : stations) {
            for (int stationLine : station.getLines()) {
                if (stationLine == lineNumber) {
                    lineStations.push_back(&station);
                    break;
                }
            }
        }

        std::sort(lineStations.begin(), lineStations.end(),
            [&](Station* a, Station* b) {
                int posA = a->getLinePosition(lineNumber);
                int posB = b->getLinePosition(lineNumber);
                return posA < posB;
            });

        // Construct and store the MetroLine
        MetroLine metroLine(lineNumber, colour, lineStations, name);
        lines.push_back(metroLine);
    }

    file.close();
}

void City::printStations() {
    std::cout << "\nStations in " << name << ":\n";
    for (const MetroLine& line : lines) {
        std::cout << "\nLine " << line.getLineID() 
                  << " (" << line.getName() << "):\n";
        int i = 1;
        for (Station* station : line.getStations()) {
            std::cout << "  " << i++ << ". " << station->getName();
            const std::vector<int>& stationLines = station->getLines();
            if (stationLines.size() > 1) {
                std::cout << " (Transfer to lines: ";
                bool first = true;
                for (int lineNum : stationLines) {
                    if (lineNum == line.getLineID()) continue;
                    if (!first) std::cout << ", ";
                    std::cout << lineNum;
                    first = false;
                }
                std::cout << ")";
            }
            std::cout << "\n";
        }
    }
}


void City::buildAdjacency(){
    for(const MetroLine& line : lines){
        const auto& lineStations = line.getStations();
        for(size_t i = 0; i < lineStations.size(); i++){
            Station* current = lineStations[i];
            if (i > 0)
                current->addEdge(lineStations[i-1], line.getLineID());
            if (i < lineStations.size()-1)
                current->addEdge(lineStations[i+1], line.getLineID());
        }
    }
}

const double City::getBasePrice() const{
    return basePrice;
}

const double City::getStationPrice() const{
    return stationPrice;
}

Station* City::getStationByName(const std::string& name){
    for(Station& station : stations){
        if(station.getName() == name){
            return &station;
        }
    }
    return nullptr;
}

const std::string City::getName() const{
    return name;
}

City City::loadCityFromCSV(const std::string& fileName, const std::string& cityName){
    std::ifstream file(fileName);
    if (!file.is_open())
        throw std::runtime_error("Failed to open cities CSV file: " + fileName);

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(ss, cell, ','))
            row.push_back(cell);

        if (row[0] == cityName) {
            City city(cityName, stod(row[1]), stod(row[2]));
            return city;
        }
    }

    throw std::runtime_error("City not found in CSV: " + cityName);
}