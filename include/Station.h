#pragma once

#include <vector>
#include <string>

class Station; 

struct Edge{
    Station* neighbour;
    int lineId;

    bool operator==(const Edge& other) const {
        return neighbour == other.neighbour && lineId == other.lineId;
    }
};

class Station{
    private:
        std::vector<int> linePositions;
        std::vector<int> lines;
        std::string city;
        std::string name;

        std::vector<Edge> edgeMap;

    public:
        Station(std::string cityName, std::vector<int> lineIds, std::vector<int> positions, std::string stationName);

        Station(const Station&) = default;
        Station& operator=(const Station&) = default;
        Station(Station&&) = default;
        Station& operator=(Station&&) = default;

        const std::vector<int>& getLines() const;
        const std::string getName() const;
        const std::vector<Edge>& getAdjacent() const;

        void addEdge(Station* neighbour, int lineNum);
        int getLinePosition(int lineNumber) const;


};