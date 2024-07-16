#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Node.h"

#include <string>
#include <vector>

struct Customer: public Node
{
    int demand{};
    std::vector<int> preferred_locker_idxs{};
    bool is_flexible{false};
    Customer(int idx, Coord coord, int demand, std::vector<int> preferred_locker_idxs, bool is_flexible);
    Customer(std::string input_line);
};
#endif