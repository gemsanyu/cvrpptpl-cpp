#ifndef LOCKER_H
#define LOCKER_H

#include "Node.h"

#include <string>

struct Locker: public Node
{
    int capacity{};
    float cost{};
    Locker(){};
    Locker(int idx, Coord coord, int service_time, int capacity, float cost);
    Locker(std::string input_line);
}; 

#endif