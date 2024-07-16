#include "Customer.h"
#include "Cvrpptpl.h"
#include "Locker.h"
#include "Mrt_line.h"
#include "Node.h"
#include "Vehicle.h"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

std::vector<std::string> read_input_lines(std::string filename);
template<typename T>
std::vector<T> read_instances(std::vector<std::string> input_lines);
std::vector<std::vector<float>> read_distance_matrix(std::vector<std::string> input_lines);


Input::Input(std::vector<std::string> input_lines)
{
    // get lines for vehicles
    std::vector<std::string>::iterator start_it = input_lines.begin()+2;
    std::vector<std::string>::iterator end_it;
    
    end_it = std::find(start_it, input_lines.end(), "depot");
    this->vehicle_input_lines = std::vector<std::string>(start_it, end_it);
    
    // read depot line
    end_it += 2;
    this->depot_input_line = *end_it;
    
    // get hd customer input lines
    start_it = end_it + 3;
    end_it = std::find(start_it, input_lines.end(), "self pickup customers");
    this->home_delivery_customer_input_lines = std::vector<std::string>(start_it, end_it);
    
    // get self pickup customer input lines
    start_it = end_it + 2;
    end_it = std::find(start_it, input_lines.end(), "flexible customers");
    this->self_pickup_customer_input_lines = std::vector<std::string>(start_it, end_it);
    
    // get flexible customer input lines
    start_it = end_it + 2;
    end_it = std::find(start_it, input_lines.end(), "lockers");
    this->flexible_customer_input_lines = std::vector<std::string>(start_it, end_it);
    
    // get lockers input lines
    start_it = end_it + 2;
    end_it = std::find(start_it, input_lines.end(), "mrt lines");
    this->locker_input_lines = std::vector<std::string>(start_it, end_it);
    
    // get mrt lines input lines
    start_it = end_it + 2;
    end_it = std::find(start_it, input_lines.end(), "distance matrix");
    this->mrt_line_input_lines = std::vector<std::string>(start_it, end_it);
    
    // get distance matrix input lines
    start_it = end_it + 2;
    this->distance_matrix_lines = std::vector<std::string>(start_it, input_lines.end());
}  

Cvrpptpl::Cvrpptpl(std::string filename){
    std::vector<std::string> input_lines = read_input_lines(filename);
    Input input{input_lines};
    this->vehicles = read_instances<Vehicle>(input.vehicle_input_lines);
    Node depot{input.depot_input_line};
    auto hd_customers = read_instances<Customer>(input.home_delivery_customer_input_lines);
    auto sp_customers = read_instances<Customer>(input.self_pickup_customer_input_lines);
    auto fx_customers = read_instances<Customer>(input.flexible_customer_input_lines);
    for (auto& fx_customer: fx_customers){
        fx_customer.is_flexible = true;
    }
    auto lockers = read_instances<Locker>(input.locker_input_lines);
    this->nodes.push_back(depot);
    this->nodes.insert(this->nodes.end(), hd_customers.begin(), hd_customers.end());
    this->nodes.insert(this->nodes.end(), sp_customers.begin(), sp_customers.end());
    this->nodes.insert(this->nodes.end(), fx_customers.begin(), fx_customers.end());
    this->nodes.insert(this->nodes.end(), lockers.begin(), lockers.end());
    this->mrt_lines = read_instances<Mrt_line>(input.mrt_line_input_lines);
    this->distance_matrix = read_distance_matrix(input.distance_matrix_lines);
    for (auto& dm: this->distance_matrix){
        for (auto& d: dm){
            std::cout<<d<<" ";
        }
        std::cout<<"\n";
    }
    
}

std::vector<std::string> read_input_lines(std::string filename)
{
    std::filesystem::path filedir = std::filesystem::current_path() / "instances";
    auto filepath = filedir/filename;
    std::ifstream file(filepath.string());
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)){
        lines.push_back(line);
    }
    return lines;
}

template<typename T>
std::vector<T> read_instances(std::vector<std::string> input_lines)
{
    std::vector<T> t_instances;
    for (std::string input_line: input_lines){
        T t_instance{input_line};
        t_instances.push_back(t_instance);
    }
    return t_instances;
}

// read distance matrix
std::vector<std::vector<float>> read_distance_matrix(std::vector<std::string> input_lines)
{
    auto num_nodes = input_lines.size();
    std::vector<std::vector<float>> distance_matrix(num_nodes);
    for (size_t i=0; i<num_nodes; i++){
        auto values = split(input_lines[i], ',');
        for (size_t j=0; j<num_nodes; j++){
            float value = std::stof(values[j]);
            distance_matrix[i].push_back(value);
        }    
    }
    return distance_matrix;
}