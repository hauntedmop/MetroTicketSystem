#pragma once

#include <vector>
#include <string>
#include "Station.h"
#include "Ticket.h"

class TicketManager{
    private:
        std::vector<Ticket> allTickets;
        std::vector<Ticket*> newTickets;
        int nextTicketID;
        City* city;
    
    public:
        TicketManager(City* linkedCity);

        void loadTickets(const std::string& fileName);
        void saveTickets(const std::string& fileName);

        Ticket* createTicket(const std::string& passengerName, const std::vector<Station*>& stationPath, City* city);
        const Ticket* findTicketbyID(int id) const;
        void printAllTickets() const;

        int generateTicketID();
};