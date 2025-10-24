#include <vector>
#include <string>

class Station{
    private:
        std::vector<int> linePositions;
        std::vector<int> lines;
        std::string city;
        std::string name;

    public:
        Station(std::string cityName, std::vector<int> lineIds, std::vector<int> positions, std::string stationName);

        const std::vector<int>& getLines() const;
};