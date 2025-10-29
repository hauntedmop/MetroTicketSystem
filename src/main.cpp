#include <iostream>
#include "City.h"
#include "PathFinder.h"
#include "Ticket.h"
#include "TicketManager.h"

City loadCityInteractive();
Station* selectStation(City& city, const std::string& prompt);
Ticket* createAndSaveTicket(TicketManager& manager, City& city);
int showMenu();
void showAllStations(City& city);
void showAllTickets(const TicketManager& manager);
void viewTicketByID(const TicketManager& manager);

City loadCityInteractive(){
    std::cout << "\n---Cities---\n";
    std::cout << "1. Pettleburg" << std::endl;
    std::cout << "2. Slateport" << std::endl;
    std::cout << "3. Lavaridge" << std::endl;
    std::string cityName;
    std::cout << "Enter the city name to Load: ";
    std::getline(std::cin, cityName);

    City city = City::loadCityFromCSV("../data/cities.csv", cityName);
    city.loadStationsFromCSV("../data/stations.csv");
    city.loadLinesFromCSV("../data/lines.csv");
    city.buildAdjacency();

    std::cout << "Loaded City " << city.getName() << std::endl;
    return city;
}

Station* selectStation(City& city, const std::string&prompt){
    std::string name;

    while (true) {
        std::cout << prompt;
        std::getline(std::cin, name);
        if (name == "q" || name == "Q") {
            std::cout << "Cancelled station selection.\n";
            return nullptr;
        }
        if (name.empty()) {
            std::cout << "Station name cannot be empty. Try again or type 'q' to quit.\n";
            continue;
        }
        Station* station = city.getStationByName(name);
        if (station)
            return station;
        std::cout << "Station not found! Try again or type 'q' to quit.\n";
    }
}

Ticket* createAndSaveTicket(TicketManager& manager, City& city){
    Station* start = selectStation(city, "Enter starting station: ");
    Station* end = selectStation(city, "Enter destination station: ");

    PathFinder finder(start, end);
    std::vector<Station*> path = finder.findPath();
    if(path.empty()){
        std::cout << "No path found!" << std::endl;
        return nullptr;
    }

    std::string passenger;
    std::cout << "Enter passenger name: ";
    std::getline(std::cin, passenger);

    Ticket* ticket = manager.createTicket(passenger, path, &city);
    std::cout << "\n---Ticket Info---\n";
    ticket->printInfo();
    std::cout << "\n---Route Instructions---\n";
    ticket->printInstructions();

    manager.saveTickets("../data/tickets.csv");
    return ticket;
}

void showAllStations(City& city){
    city.printStations();
}

void showAllTickets(const TicketManager& manager){
    std::cout << "\n---All Tickets---\n";
    manager.printAllTickets();
}

void viewTicketByID(const TicketManager& manager) {
    int id;
    std::cout << "Enter ticket ID: ";
    std::cin >> id;
    std::cin.ignore();

    const Ticket* ticket = manager.findTicketbyID(id);
    if (!ticket) {
        std::cout << "No ticket found with ID " << id << std::endl;
        return;
    }

    std::cout << "\n--- Ticket Details ---\n";
    ticket->printInfo();
    std::cout << "\n--- Instructions ---\n";
    ticket->printInstructions();
}

int showMenu() {
    int choice = 0;
    while (true) {
        std::cout << "\n--- Metro Ticketing System ---\n";
        std::cout << "1. Buy Ticket" << std::endl;
        std::cout << "2. View All Tickets" << std::endl;
        std::cout << "3. View Ticket by ID" << std::endl;
        std::cout << "4. See Stations" << std::endl;
        std::cout << "5. Quit" << std::endl;
        std::cout << "Select an option: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "Invalid input! Please enter a number between 1 and 5.\n";
            continue;
        }

        std::cin.ignore(100, '\n');

        if (choice >= 1 && choice <= 5)
            return choice;

        std::cout << "Invalid choice! Please try again.\n";
    }
}

int main() {
    City city = loadCityInteractive();
    TicketManager manager(&city);
    manager.loadTickets("../data/tickets.csv");

    bool running = true;
    while (running) {
        int choice = showMenu();
        switch (choice) {
            case 1:
                createAndSaveTicket(manager, city);
                break;
            case 2:
                showAllTickets(manager);
                break;
            case 3:
                viewTicketByID(manager);
                break;
            case 4:
                showAllStations(city);
                break;
            case 5:
                running = false;
                break;
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}
