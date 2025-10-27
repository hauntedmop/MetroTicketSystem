#include <iostream>
#include "City.h"
#include "PathFinder.h"

int main(){
    try{
        City pettleburg("Pettleburg");

        pettleburg.loadStationsFromCSV("../data/stations.csv");
        pettleburg.loadLinesFromCSV("../data/lines.csv");
        pettleburg.buildAdjacency();

        std::cout << "Stations in Pettleburg Metro: " << std::endl;
        pettleburg.printStations();
        std::cout << std::endl;
    }

    catch(const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}