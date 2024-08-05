#ifndef MRT_LINE_H
#define MRT_LINE_H

#include "Locker.h"

#include <string>

struct Mrt_line
{   
    int idx{};
    int start_station_node_idx{};
    int end_station_node_idx{};
    int capacity{};
    float cost{};
    Mrt_line(){};
    Mrt_line(int start_station_node_idx, int end_station_node_idx, int capacity, float cost);
    Mrt_line(std::string input_line);
};
#endif