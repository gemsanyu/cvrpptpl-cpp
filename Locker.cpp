#include "Locker.h"
#include "Node.h"
#include "utils.h"

#include <string>
#include <vector>

Locker::Locker(int idx, Coord coord, int service_time, int capacity, float cost)
{
    this->idx = idx;
    this->coord = coord;
    this->capacity = capacity;
    this->cost = cost;
    this->service_time = service_time;
}

Locker::Locker(std::string input_line)
{
    auto values = split(input_line, ',');
    this->idx = std::stoi(values[0]);
    float x{std::stof(values[1])};
    float y{std::stof(values[2])};
    Coord coord{x,y};
    this->coord = coord;
    this->service_time = std::stoi(values[3]);
    this->capacity = std::stoi(values[4]);
    this->cost = std::stof(values[5]);
}