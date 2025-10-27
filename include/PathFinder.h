#pragma once

#include "Station.h"
#include <vector>
#include <string>

class PathFinder{
    private:
        Station* startStation;
        Station* endStation;
        std::vector<Station*> path;
        std::vector<Station*> reconstructPath(std::map<Station*, Station*>& parent, Station* endStation);
                
    public:
        PathFinder(Station* start, Station* end);
        std::vector<Station*> findPath();

};