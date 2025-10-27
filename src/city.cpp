#include "City.h"
#include "Station.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

City::City(std::string cityName)
    : name(cityName)
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

void City::loadLinesFromCSV(const std::string& fileName){
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

        std::string cityName = row[0];
        if(cityName != name) continue;
        int lineNumber = stoi(row[1]);
        std::string colour = row[2];
        std::vector<Station*> lineStations;
        for(Station& station : stations){
            for(int stationLine : station.getLines()){
                if(stationLine == lineNumber){
                    lineStations.push_back(&station);
                }
            }
        }

        MetroLine line = MetroLine(lineNumber, colour, lineStations, name);
        lines.push_back(line);
    }
    file.close();
}

void City::printStations(){
    for(Station& station : stations){
        std::cout << station.getName() << std::endl;
    }
}

void City::buildAdjacency(){
    for(const MetroLine& line : lines){
        const auto& lineStations = line.getStations();
        for(size_t i = 0; i < lineStations.size(); i++){
            Station* current = lineStations[i];
            if (i > 0)
                current->addAdjacent(lineStations[i-1]);
            if (i < lineStations.size()-1)
                current->addAdjacent(lineStations[i+1]);
        }
    }
}