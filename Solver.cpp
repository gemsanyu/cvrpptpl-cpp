#include "Customer.h"
#include "Mrt_line.h"
#include "Solution.h"
#include "Solver.h"
#include "Task.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <vector>

#define FLT_MAX std::numeric_limits<float>::max()

std::vector<std::vector<Task>> generate_customers_tasks(const Cvrpptpl& problem);
Vec_cp generate_random_customer_priorities(const Cvrpptpl& problem);
Task_assignment get_best_task_assignment(const Cvrpptpl& problem, const Solution& solution, const Task& task);

void Solver::init(const Cvrpptpl& problem)
{
    this->customers_tasks = generate_customers_tasks(problem);
}

Solution Solver::solve(const Cvrpptpl& problem)
{
    this->init(problem);
    Solution solution = this->generate_initial_solution(problem);
    return solution;
}

Solution Solver::generate_initial_solution(const Cvrpptpl& problem)
{
    Solution solution{};
    solution.init(problem);
    Vec_cp customer_priorities = generate_random_customer_priorities(problem);
    for (auto& cp: customer_priorities){
        auto customer = problem.get_customer(cp.cust_idx);
        auto task_assignment = this->get_customer_best_task_assignment(problem, solution, customer);
        if (task_assignment.task != nullptr){
            solution.apply_task_assignment(problem, task_assignment);
        }
    }
    return solution;
}

Task_assignment Solver::get_customer_best_task_assignment(const Cvrpptpl& problem, const Solution& solution, const Customer& customer)
{
    Task_assignment best_ta{nullptr,0,0,FLT_MAX};
    for (auto& task: this->customers_tasks[customer.idx]){
        auto p_ta = get_best_task_assignment(problem, solution, task);
        if ((best_ta.task == nullptr && p_ta.task != nullptr) || (best_ta.delta_cost>p_ta.delta_cost)){
            best_ta = p_ta;
        }
    }
    return best_ta;
}


Task_assignment get_best_task_assignment(const Cvrpptpl& problem, const Solution& solution, const Task& task)
{
    Task_assignment best_ta{nullptr, 0, 0, FLT_MAX};
    for (int route_idx=0; route_idx<problem.num_vehicles;route_idx++){
        int route_len = solution.vehicle_tasks[route_idx].size();
        for (int pos=0;pos<=route_len;pos++){
            // std::cout <<task.customer_idx<<" "<<task.destination_idx<<" "<< route_len << " " << pos <<"\n";
            if (solution.is_insertion_feasible(problem, task, route_idx, pos)){
                float delta_cost = solution.compute_insertion_cost(problem, task, route_idx, pos);
                if (delta_cost < best_ta.delta_cost){
                    best_ta.task = &task;
                    best_ta.route_idx = route_idx;
                    best_ta.pos = pos;
                    best_ta.delta_cost = delta_cost;
                }
            }
        }
    }   
    return best_ta;
}

Vec_cp generate_random_customer_priorities(const Cvrpptpl& problem)
{
    Vec_cp customer_priorities{};
    for (auto& customer: problem.customers){
        float priority =  (float) rand()/ (float)RAND_MAX;
        if (not customer.preferred_locker_idxs.empty()){
            priority += 1;
        }
        Customer_priority cp{customer.idx, priority};
        customer_priorities.push_back(cp);
    }
    sort(customer_priorities.begin(), customer_priorities.end());
    return customer_priorities;
}


std::vector<std::vector<Task>> generate_customers_tasks(const Cvrpptpl& problem)
{
    std::map<int, Mrt_line> e_idx_mrt_line_map;
    for (auto& mrt_line: problem.mrt_lines){
        e_idx_mrt_line_map[mrt_line.end_station_node_idx] = mrt_line;
    }
    std::vector<std::vector<Task>> customers_tasks(problem.num_customers+1);
    for (auto& customer: problem.customers){
        customers_tasks[customer.idx] = generate_customer_tasks(problem, customer, e_idx_mrt_line_map);
    }
    return customers_tasks;
}
