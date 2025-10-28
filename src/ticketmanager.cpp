#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Ticket.h"
#include "Station.h"
#include "TicketManager.h"

TicketManager::TicketManager(City* linkedCity)
    : city(linkedCity)
{

}

void TicketManager::loadTickets(const std::string& fileName){
    std::ifstream file(fileName);
    if(!file.is_open())
        throw std::runtime_error("No CSV file opened");

    std::string line;
    nextTicketID = 1;
    while(std::getline(file,line)){
        if(line.empty()) continue;

        std::stringstream ss(line);
        std::string cell;
        std::vector<std::string> row;

        while(std::getline(ss, cell, ',')){
            row.push_back(cell);
        }

        int ticketID = stoi(row[0]);
        if(nextTicketID < ticketID)
            nextTicketID = ticketID+1;
        std::string passenger = row[1];
        std::string cityName = row[2];
        if(cityName != city->getName()) continue;
        double price = stod(row[3]);
        std::vector<Station*> path;
        for(size_t i = 4; i < row.size(); i++){
            Station* station = city->getStationByName(row[i]);
            if (station)
                path.push_back(station);
        }
        Ticket ticket(ticketID, path, passenger, city);
        allTickets.push_back(ticket);
    }

    
}

void TicketManager::saveTickets(const std::string& fileName) const{
    std::ofstream file(fileName, std::ios::app);
    if(!file.is_open())
        throw std::runtime_error("No CSV file opened");

    for(const Ticket& ticket : newTickets){
        file << ticket.getId() << ","
             << ticket.getPassengerName() << ","
             << city->getName() << ","
             << ticket.getPrice();
            
        for (size_t i = 0; i < ticket.getPath().size(); i++) {
            file << ticket.getPath()[i]->getName();
            if (i != ticket.getPath().size() - 1)
                file << ",";
        }

        file << "\n";
    }

    file.close();
}

const Ticket* TicketManager::findTicketbyID(int id) const{
    for(const Ticket& ticket : allTickets)
        if(ticket.getId() == id)
            return &ticket;
    return nullptr;
}

int TicketManager::generateTicketID(){
    return nextTicketID++;
}

Ticket* TicketManager::createTicket(const std::string& passengerName, const std::vector<Station*>& stationPath, City* city){
    Ticket ticket(generateTicketID(), stationPath, passengerName, city);
    allTickets.push_back(ticket);
    newTickets.push_back(allTickets.back());
    return &allTickets.back();
}