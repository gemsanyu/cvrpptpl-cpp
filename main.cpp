#include "Cvrpptpl.h"
#include "Mrt_line.h"
#include "Task.h"
#include "Solver.h"

#include <map>
#include <string>

int main()
{   

    const std::string filename{"nn_14_clm_c_dlm_c_lcr_0.6_llm_c_pr_0.5_fr_0.0_fcm_e_nc_10_nl_3_nv_2_idx_0.txt"};
    Cvrpptpl problem{filename};
    Solver solver{};
    auto solution = solver.solve(problem);
    solution.describe(problem);
}