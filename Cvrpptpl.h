#ifndef CVRPPTPL_H
#define CVRPPTPL_H

#include "Mrt_line.h"
#include "Node.h"
#include "Vehicle.h"
#include "utils.h"

#include <string>
#include <vector>

struct Cvrpptpl
{
    std::vector<std::vector<float>> distance_matrix;
    std::vector<Mrt_line> mrt_lines;
    std::vector<Node> nodes;
    std::vector<Vehicle> vehicles;
    Cvrpptpl(std::string filename);
};

struct Input{
    std::vector<std::string> vehicle_input_lines;
    std::string depot_input_line;
    std::vector<std::string> home_delivery_customer_input_lines;
    std::vector<std::string> self_pickup_customer_input_lines;
    std::vector<std::string> flexible_customer_input_lines;
    std::vector<std::string> locker_input_lines;
    std::vector<std::string> mrt_line_input_lines;
    std::vector<std::string> distance_matrix_lines;
    Input(std::vector<std::string> input_lines);
};

#endif