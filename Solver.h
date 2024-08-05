#ifndef SOLVER_H
#define SOLVER_H

#include "Cvrpptpl.h"
#include "Mrt_line.h"
#include "Solution.h"
#include "Task.h"

#include <map>
#include <vector>

struct Customer_priority
{
    int cust_idx;
    float priority;
    friend bool operator<(const Customer_priority& cp1, const Customer_priority& cp2)
    {
        return cp1.priority < cp2.priority;
    }
};

typedef std::vector<Customer_priority> Vec_cp;

struct Solver
{
    std::vector<std::vector<Task>> customers_tasks;

    Solver(){};
    Solution solve(const Cvrpptpl& problem);
    void init(const Cvrpptpl& problem);
    Solution generate_initial_solution(const Cvrpptpl& problem);
    Task_assignment get_customer_best_task_assignment(const Cvrpptpl& problem, const Solution& solution, const Customer& customer);
};

#endif