#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include "Station.h"
#include "PathFinder.h"


PathFinder::PathFinder(Station* start, Station* end)
    : startStation(start), endStation(end)
{

}

std::vector<Station*> PathFinder::findPath(){
    std::queue<Station*> queue;
    std::map<Station*, Station*> parent;
    std::set<Station*> visited;

    queue.push(startStation);
    parent[startStation] = nullptr;

    Station* currentStation;
    visited.insert(startStation);

    while(!queue.empty()){
        currentStation = queue.front();
        queue.pop();

        if(currentStation == endStation)
            return reconstructPath(parent, endStation);

        for(Edge edge : currentStation->getAdjacent()){
            Station* neighbour = edge.neighbour;
            if(visited.find(neighbour) == visited.end()){
                queue.push(neighbour);
                visited.insert(neighbour);
                parent[neighbour] = currentStation;
            }
        }
    }

    return {};
}

std::vector<Station*> PathFinder::reconstructPath(std::map<Station*, Station*>& parent, Station* endStation){
    std::vector<Station*> path;
    for(Station* station = endStation; station != nullptr; station = parent[station])
        path.push_back(station);
    std::reverse(path.begin(), path.end());
    return path;
}