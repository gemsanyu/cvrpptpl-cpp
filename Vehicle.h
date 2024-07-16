#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

struct Vehicle
{
    int idx{};
    int capacity{};
    float cost{};    
    Vehicle(){};
    Vehicle(int idx,int capacity,float cost);
    Vehicle(std::string input_line);
};
#endif