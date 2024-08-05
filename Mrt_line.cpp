#include "Mrt_line.h"
#include "utils.h"

#include <string>

Mrt_line::Mrt_line(int start_station_node_idx, int end_station_node_idx, int capacity, float cost)
{
    this->start_station_node_idx = start_station_node_idx;
    this->end_station_node_idx = end_station_node_idx;
    this->capacity = capacity;
    this->cost = cost;
}

Mrt_line::Mrt_line(std::string input_line)
{
    auto values = split(input_line, ',');
    this->start_station_node_idx = std::stoi(values[0]);
    this->end_station_node_idx = std::stoi(values[1]);
    this->capacity = std::stoi(values[2]);
    this->cost = std::stof(values[3]);
}