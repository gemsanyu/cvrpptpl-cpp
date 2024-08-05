#include "Customer.h"
#include "Cvrpptpl.h"
#include "Task.h"

#include <iostream>
#include <vector>

bool Task::is_locker() const
{
    return this->customer_idx != this->locker_idx;
}

bool Task::is_mrt() const
{
    return this->is_locker() && (this->destination_idx != this->locker_idx);
}

std::vector<Task> generate_customer_tasks(const Cvrpptpl& problem, 
                                        const Customer& customer, 
                                        const std::map<int, Mrt_line>& e_idx_mrt_line_map)
{
    std::vector<Task> tasks;
    if (customer.preferred_locker_idxs.empty() || customer.is_flexible){
        // home delivery
        Task home_delivery_task{customer.idx, customer.idx, customer.idx, customer.demand, 0., 0. , -1};
        tasks.push_back(home_delivery_task);
    }

    for (int locker_idx: customer.preferred_locker_idxs){
        // check if it is also end station

        // add locker task
        auto locker = problem.get_locker(locker_idx);
        float total_locker_cost = locker.cost * customer.demand;
        Task locker_delivery_task{customer.idx, locker.idx, locker.idx, customer.demand, total_locker_cost, 0., -1};
        tasks.push_back(locker_delivery_task);
        // add mrt line task
        auto map_it = e_idx_mrt_line_map.find(locker_idx);
        
        if (map_it==e_idx_mrt_line_map.end()){
            continue;
        }
        auto mrt_line = map_it->second;
        float total_mrt_cost = mrt_line.cost * customer.demand;
        Task mrt_line_delivery_task{customer.idx, locker.idx, mrt_line.start_station_node_idx, customer.demand, total_locker_cost, 0., mrt_line.idx};    
        tasks.push_back(mrt_line_delivery_task);
    }

    return tasks;
}

