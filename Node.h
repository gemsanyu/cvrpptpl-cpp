#ifndef NODE_H
#define NODE_H

#include <string>


struct Coord
{
    float x {};
    float y {};
};

struct Node
{
    int idx {};
    Coord coord;
    int service_time;
    Node(){};
    Node(int idx, int service_time, Coord coord);
    Node(std::string input_line);
};

#endif