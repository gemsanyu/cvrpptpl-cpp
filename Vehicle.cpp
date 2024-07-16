#include "Vehicle.h"
#include "utils.h"

#include <string>

Vehicle::Vehicle(std::string input_line)
{
    auto values = split(input_line, ',');
    this->idx=std::stoi(values[0]);
    this->capacity=std::stoi(values[1]);
    this->cost=std::stof(values[2]);
}