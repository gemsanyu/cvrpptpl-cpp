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
    Node(){};
    Node(int idx, Coord coord);
    Node(std::string input_line);
};

#endif