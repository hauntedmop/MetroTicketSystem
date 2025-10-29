#include <vector>
#include <string>
#include <iostream>
#include "Ticket.h"
#include "Station.h"

Ticket::Ticket(int id, std::vector<Station*> path, std::string name, City* city)
    : ticketID(id), stationPath(path), passengerName(name), city(city)
{
    cityName = city->getName();
    calculatePrice();
}

const int Ticket::getId() const{
    return ticketID;
}

const double Ticket::getPrice() const{
    return price;
}

const std::vector<Station*> Ticket::getPath() const{
    return stationPath;
}

void Ticket::printInfo() const{
    if(stationPath.empty()){
        std::cout << "Invalid Ticket path" << std::endl;
        return;
    }
    std::cout << "Passenger name is: " << passengerName << std::endl;
    if(stationPath.size() >= 1)
        std::cout << "Starting station is: " << stationPath[0]->getName() << std::endl;
    if(stationPath.size() >= 2)
        std::cout << "Destination station is: " << stationPath.back()->getName() << std::endl;
    std::cout << "Price is: " << price << std::endl;
}

void Ticket::printInstructions() const{
    if(stationPath.size() < 2){
        std::cout << "No route instructions available (path too short). " << std::endl;
        return;
    }
    int currentLine = -1;
    for(const Edge& edge: stationPath[0]->getAdjacent())
        if(edge.neighbour == stationPath[1]){
            currentLine = edge.lineId;
            break;
        }
    std::cout << "Start from station: " << stationPath[0]->getName() << " on line: " << currentLine << std::endl;
    int lastline = currentLine;
    for(size_t i = 1; i < stationPath.size() -1; i++){
        for(const Edge& edge: stationPath[i]->getAdjacent())
            if(edge.neighbour == stationPath[i+1]){
                currentLine = edge.lineId;
                break;
            }
        if(currentLine!=lastline){
            std::cout << "Switch from line " << lastline << " to line " << currentLine
                      << " at metro station " << stationPath[i]->getName() << std::endl;
            lastline = currentLine;
        }
    }
    std::cout << "Finally, exit at station " << stationPath.back()->getName() << " on line " << currentLine << std::endl;
}

void Ticket::calculatePrice(){
    if(!city || stationPath.size() < 2){
        price = 0;
        return;
    }
    price = city->getBasePrice() + (stationPath.size()-1)*(city->getStationPrice());
}

const std::string Ticket::getPassengerName() const{
    return passengerName;
}