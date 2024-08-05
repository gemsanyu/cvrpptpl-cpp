#include "Cvrpptpl.h"
#include "Solution.h"

#include <iostream>

Vec_int init_locker_capacities(const Cvrpptpl& problem);
Vec_int init_vehicle_capacities(const Cvrpptpl& problem);

void Solution::init(const Cvrpptpl& problem)
{
    this->locker_loads = Vec_int(problem.num_nodes);
    this->lockers_route_idx = Vec_int(problem.num_nodes, -1);
    this->mrt_line_loads = Vec_int(problem.num_mrt_lines);
    this->vehicle_loads = Vec_int(problem.num_vehicles);
    this->vehicle_tasks = std::vector<Task_seq>(problem.num_vehicles);
    this->current_times = Vec_float(problem.num_vehicles);
    this->is_served = Vec_bool(problem.num_nodes);
    this->num_served_customers = 0;
}

bool Solution::is_locker_insertion_feasible(const Cvrpptpl& problem,  const Task& task, int route_idx, int pos) const
{
    // check if this locker is already visited in another route
    int route_idx_of_locker = this->lockers_route_idx[task.locker_idx];
    bool locker_is_served = route_idx_of_locker >-1;
    if (locker_is_served){
        if (route_idx != route_idx_of_locker){
            return false;
        }
        // can only be inserted after/before the same locker/mrt task
        bool is_prev_task_same = false;
        bool is_next_task_same = false;
        auto& v_tasks = this->vehicle_tasks[route_idx];
        if (pos!=0){
            auto previous_task = v_tasks[pos-1];
            if (previous_task->locker_idx==task.locker_idx && previous_task->destination_idx == task.destination_idx){
                is_prev_task_same = true;
            } 
        }
        if (pos!=v_tasks.size()){
            auto next_task = v_tasks[pos];
            if (next_task->locker_idx==task.locker_idx && next_task->destination_idx == task.destination_idx){
                is_next_task_same = true;
            } 
        }
        if (!is_prev_task_same && !is_next_task_same){
            return false;
        }   
    }

    const Customer& customer = problem.get_customer(task.customer_idx); 
    auto& locker_cap = problem.get_locker(task.locker_idx).capacity;
    if (this->locker_loads[task.locker_idx] + customer.demand > locker_cap){
        return false;
    }
    if (task.is_mrt()){
        auto& mrt_line = problem.mrt_lines[task.mrt_line_idx];
        if (customer.demand + this->mrt_line_loads[task.mrt_line_idx] > mrt_line.capacity){
            return false;
        }
    }    
    return true;
}

void Solution::apply_task_assignment(const Cvrpptpl& problem, const Task_assignment& task_assignment)
{
    int route_idx = task_assignment.route_idx;
    int pos = task_assignment.pos;
    int demand = task_assignment.task->demand;
    this->vehicle_tasks[route_idx].insert(this->vehicle_tasks[route_idx].begin()+pos, task_assignment.task);
    this->is_served[task_assignment.task->customer_idx] = true;
    this->num_served_customers++; 
    // update load/capacity of vehicle,locker,mrt
    this->vehicle_loads[route_idx] += demand;
    if (task_assignment.task->is_locker()){
        this->locker_loads[task_assignment.task->locker_idx] += demand;
        this->lockers_route_idx[task_assignment.task->locker_idx] = route_idx;
    }
    if (task_assignment.task->is_mrt()){
        this->mrt_line_loads[task_assignment.task->mrt_line_idx] += demand;
    }
}

bool Solution::is_insertion_feasible(const Cvrpptpl& problem,  const Task& task, int route_idx, int pos) const
{
    if (this->is_served[task.customer_idx]){
        return false;
    }
    bool is_hd = !task.is_locker();
    if (!is_hd && !is_locker_insertion_feasible(problem, task, route_idx, pos)){
        return false;
    }
    const Customer& customer = problem.get_customer(task.customer_idx); 
    auto& vehicle_cap = problem.vehicles[route_idx].capacity;
    if (this->vehicle_loads[route_idx] + customer.demand > vehicle_cap){
        return false;
    }
    return true;
}

float Solution::compute_insertion_cost(const Cvrpptpl& problem, const Task& task, int route_idx, int pos) const
{
    auto& v_tasks = this->vehicle_tasks[route_idx];
    int previous_node_idx = 0;
    int next_node_idx = 0;
    if (pos>0){
        previous_node_idx = v_tasks[pos-1]->destination_idx;
    }
    if (pos<v_tasks.size()){
        next_node_idx = v_tasks[pos]->destination_idx;
    }
    const auto& dm = problem.distance_matrix;
    float delta_travel_time = dm[previous_node_idx][task.destination_idx] + dm[task.destination_idx][next_node_idx] - dm[previous_node_idx][next_node_idx];
    float delta_travel_cost = delta_travel_time*problem.vehicles[route_idx].cost;
    float delta_cost = delta_travel_cost + task.mrt_cost + task.locker_cost;
    return delta_cost;
}

Vec_int init_locker_capacities(const Cvrpptpl& problem)
{
    Vec_int locker_capacities(problem.num_nodes);
    for (auto& locker: problem.lockers){
        locker_capacities[locker.idx] = locker.capacity;
    }
    return locker_capacities;
}


Vec_int init_vehicle_capacities(const Cvrpptpl& problem){
    Vec_int vehicle_capacities(problem.num_vehicles);
    for (int i=0;i<problem.vehicles.size();i++){
        vehicle_capacities[i] = problem.vehicles[i].capacity;
    }
    return vehicle_capacities;
}


void Solution::describe(const Cvrpptpl& problem)
{
    for (int v_idx=0;v_idx<problem.num_vehicles;v_idx++){
        std::cout << "Vehicle " << v_idx << ":\n";
        auto& v_tasks = this->vehicle_tasks[v_idx];
        if (v_tasks.empty()){
            std::cout<<"++++++++++++++++++++++\n";
            continue;
        }
        std::cout << "Load/Capacity:\t" << this->vehicle_loads[v_idx] <<"/"<<problem.vehicles[v_idx].capacity<<"\n";
        std::cout << "Served customers:\n";
        for (auto& task: v_tasks){
            std::cout<<task->customer_idx<<" ";
            if (task->is_locker()){
                std::cout<<"pickup at locker " <<task->locker_idx<<" ";
            }
            if (task->is_mrt()){
                auto& mrt = problem.mrt_lines[task->mrt_line_idx];
                std::cout<<"via MRT line "<<mrt.start_station_node_idx<<"->"<<mrt.end_station_node_idx;
            }
            std::cout<<"\n";
        }
        std::cout<<"---------------\n";
        std::cout << "Routes:\n";
        std::cout << 0 <<" ";
        for (int i=0;i<v_tasks.size();i++){
            if (i>0 && v_tasks[i-1]->destination_idx == v_tasks[i]->destination_idx){
                continue;
            }
            std::cout<<v_tasks[i]->destination_idx<<" ";
        }
        std::cout << 0 <<"\n";
        std::cout <<"++++++++++++++++++++++\n";    
    }
    std::cout << "Cost:\n";
    std::cout << "Travel Cost: " << this->get_travel_cost(problem) <<  "\n";
    std::cout << "Locker Cost: " << this->get_locker_cost(problem) << "\n";
    std::cout << "MRT Cost: " << this->get_mrt_cost(problem) << "\n";

}

float Solution::get_travel_cost(const Cvrpptpl& problem) const
{
    float total_travel_cost = 0;
    for (int v_idx=0; v_idx<problem.num_vehicles; v_idx++){
        auto v_tasks= this->vehicle_tasks[v_idx];
        int cur_node_idx = 0;
        for (auto& task: v_tasks){
            float dist = problem.distance_matrix[cur_node_idx][task->destination_idx];
            total_travel_cost += dist*problem.vehicles[v_idx].cost;
            cur_node_idx = task->destination_idx;
        }
        float dist = problem.distance_matrix[cur_node_idx][0];
        total_travel_cost += dist*problem.vehicles[v_idx].cost;
    }
    return total_travel_cost;
}

float Solution::get_locker_cost(const Cvrpptpl& problem) const
{
    float total_locker_cost = 0;
    for (auto& v_tasks: this->vehicle_tasks){
        for (auto& task: v_tasks){
            total_locker_cost += task->locker_cost;
        }
    }
    return total_locker_cost;
}

float Solution::get_mrt_cost(const Cvrpptpl& problem) const
{
    float total_mrt_cost = 0;
    for (auto& v_tasks: this->vehicle_tasks){
        for (auto& task: v_tasks){
            total_mrt_cost += task->mrt_cost;
        }
    }
    return total_mrt_cost;
}