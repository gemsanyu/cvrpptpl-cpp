#include "Customer.h"
#include "Node.h"
#include "utils.h"

#include <vector>


Customer::Customer(int idx, Coord coord, int demand, std::vector<int> preferred_locker_idxs, bool is_flexible)
{
    this->idx = idx;
    this->coord = coord;
    this->demand = demand;
    this->preferred_locker_idxs = preferred_locker_idxs;
    this->is_flexible = is_flexible;
}

Customer::Customer(std::string input_line)
{
    auto values = split(input_line, ',');
    this->idx = std::stoi(values[0]);
    float x{std::stof(values[1])};
    float y{std::stof(values[2])};
    Coord coord{x,y};
    this->coord = coord;
    this->demand = std::stoi(values[3]);
    // extract preferred locker idxs if any
    if (values.size()<5) {
        return;
    }
    auto preferred_locker_idxs_str = split(values[4], '-');
    for (auto& locker_idx_str: preferred_locker_idxs_str){
        this->preferred_locker_idxs.push_back(std::stoi(locker_idx_str));
    }
}