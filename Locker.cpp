#include "Locker.h"
#include "Node.h"
#include "utils.h"

#include <string>
#include <vector>

Locker::Locker(int idx, Coord coord, int capacity, float cost)
{
    this->idx = idx;
    this->coord = coord;
    this->capacity = capacity;
    this->cost = cost;
}

Locker::Locker(std::string input_line)
{
    auto values = split(input_line, ',');
    this->idx = std::stoi(values[0]);
    this->capacity = std::stoi(values[3]);
    this->cost = std::stof(values[4]);
    float x{std::stof(values[1])};
    float y{std::stof(values[2])};
    Coord coord{x,y};
    this->coord = coord;
}