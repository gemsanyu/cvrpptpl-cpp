#ifndef CVRPPTPL_H
#define CVRPPTPL_H

#include "Customer.h"
#include "Locker.h"
#include "Mrt_line.h"
#include "Node.h"
#include "Vehicle.h"
#include "utils.h"

#include <string>
#include <vector>

struct Cvrpptpl
{
    int num_customers{};
    int num_home_delivery_customers{};
    int num_self_pickup_customers{};
    int num_flexible_customers{};
    int num_nodes{};
    int num_vehicles{};
    int num_mrt_lines{};
    int num_lockers{};

    std::vector<std::vector<float>> distance_matrix;
    std::vector<Mrt_line> mrt_lines;
    Node depot;
    std::vector<Customer> customers;
    std::vector<Locker> lockers;
    std::vector<Vehicle> vehicles;
    Cvrpptpl(std::string filename);
    const Customer& get_customer(int cust_idx) const;
    const Locker& get_locker(int locker_idx) const;
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