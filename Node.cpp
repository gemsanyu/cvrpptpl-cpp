#include "Node.h"
#include "utils.h"

#include <string>


Node::Node(std::string input_line)
{
    auto values = split(input_line, ',');
    this->idx = std::stoi(values[0]);
    float x{std::stof(values[1])};
    float y{std::stof(values[2])};
    this->coord = {x,y};
    // this->service_time = std::stoi(values[3]);
}