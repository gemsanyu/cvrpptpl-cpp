#ifndef SOLUTION_H
#define SOLUTION_H

#include "Cvrpptpl.h"
#include "Task.h"

#include <vector>

typedef std::vector<int> Vec_int;
typedef std::vector<float> Vec_float;
typedef std::vector<bool> Vec_bool;

struct Cost
{
    float travel_cost;
    float mrt_cost;
    float locker_cost;    
};

struct Solution
{
    Vec_int locker_loads;        
    Vec_int lockers_route_idx;
    Vec_int vehicle_loads;
    Vec_int mrt_line_loads;
    Vec_float current_times;
    Vec_bool is_served;
    std::vector<Task_seq> vehicle_tasks;
    int num_served_customers{};

    Solution(){};
    void init(const Cvrpptpl& problem);
    void apply_task_assignment(const Cvrpptpl& problem, const Task_assignment& task_assignment);
    bool is_insertion_feasible(const Cvrpptpl& problem,  const Task& task, int route_idx, int pos) const;
    bool is_locker_insertion_feasible(const Cvrpptpl& problem,  const Task& task, int route_idx, int pos) const;
    float compute_insertion_cost(const Cvrpptpl& problem, const Task& task, int route_idx, int pos) const;
    float get_travel_cost(const Cvrpptpl& problem) const;
    float get_locker_cost(const Cvrpptpl& problem) const;
    float get_mrt_cost(const Cvrpptpl& problem) const;
    void describe(const Cvrpptpl& problem);
    // bool is_feasible();
};

#endif