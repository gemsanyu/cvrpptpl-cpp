#ifndef TASK_H
#define TASK_H

#include "Customer.h"
#include "Cvrpptpl.h"

#include <map>
#include <vector>


struct Task
{
    int customer_idx{};
    int locker_idx{};
    int destination_idx{};
    int demand{};
    float locker_cost{};
    float mrt_cost{};
    int mrt_line_idx{};

    bool is_locker() const;
    bool is_mrt() const;
};


struct Task_assignment
{
    const Task* task;
    int route_idx;
    int pos;
    float delta_cost;
};

typedef std::vector<const Task*> Task_seq;
std::vector<Task> generate_customer_tasks(const Cvrpptpl& problem, const Customer& customer, const std::map<int, Mrt_line>& e_idx_mrt_line_map);

#endif