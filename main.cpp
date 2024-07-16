#include "Cvrpptpl.h"

// #include <fstream>
// #include <iostream>
// #include <map>
#include <string>
// #include <vector>

int main()
{   
    const std::string filename{"nn_31_dlm_r_lcr_0.6_llm_r_pr_0.3_fr_0.3_fcm_e_nc_20_nl_10_nv_10_idx_0.txt"};
    Cvrpptpl problem{filename};
    // const std::string instance_dir{"C:\\Users\\USER\\cpp\\CVRP-PT-PL\\instances"};
    // const std::string instance_name{"nn_31_dlm_r_lcr_0.6_llm_r_pr_0.3_fr_0.3_fcm_e_nc_20_nl_10_nv_10_idx_0.txt"};
    // const std::string instance_path{instance_dir + "\\" + instance_name};
    // std::ifstream file(instance_path);
    // std::string line;
    // std::vector<std::string> lines;
    // while (std::getline(file, line)){
    //     lines.push_back(line);
    // }
    // int line_idx{2}; 
    // line = lines[line_idx];
    // std::vector<Vehicle> vehicles;
    // while (line.find("depot")==std::string::npos){
    //     auto values = split(line, ',');
    //     int idx{std::stoi(values[0])};
    //     int capacity{std::stoi(values[1])};
    //     float cost{std::stof(values[2])};
    //     const Vehicle vehicle{idx,capacity,cost};
    //     vehicles.push_back(vehicle);
    //     line_idx++;
    //     line = lines[line_idx];
    // }
    // line_idx += 2;
    // // read the nodes
    // std::vector<Node> nodes;
    // // read depot
    // line = lines[line_idx];
    // auto values = split(line, ',');
    // int idx{std::stoi(values[0])};
    // float x{std::stof(values[1])};
    // float y{std::stof(values[2])};
    // const Coord depot_coord{x,y};
    // const Node depot{idx, depot_coord};
    // nodes.push_back(depot);
    // // read home delivery customer
    // line_idx += 3;
    // line = lines[line_idx];
    // while (line.find("self pickup")==std::string::npos){
    //     auto values = split(line, ',');
    //     int idx{std::stoi(values[0])};
    //     float x{std::stof(values[1])};
    //     float y{std::stof(values[2])};
    //     int demand{std::stoi(values[3])};
    //     const Coord coord{x,y};
    //     const Customer hd_customer{idx, coord, demand, {}, false};
    //     nodes.push_back(hd_customer);
    //     line_idx++;
    //     line = lines[line_idx];
    // }
    // // read self pickup customer
    // line_idx+=2;
    // line = lines[line_idx];
    // while (line.find("flexible")==std::string::npos){
    //     auto values = split(line, ',');
    //     int idx{std::stoi(values[0])};
    //     float x{std::stof(values[1])};
    //     float y{std::stof(values[2])};
    //     int demand{std::stoi(values[3])};
    //     auto preferred_locker_idxs_str = split(values[4], '-');
    //     std::vector<int> preferred_locker_idxs{};
    //     for (auto& locker_idx_str: preferred_locker_idxs_str){
    //         preferred_locker_idxs.push_back(std::stoi(locker_idx_str));
    //     }
    //     const Coord coord{x,y};
    //     const Customer sp_customer{idx, coord, demand, preferred_locker_idxs, false};
    //     nodes.push_back(sp_customer);
    //     line_idx++;
    //     line = lines[line_idx];
    // }
    // // read flexible customer
    // line_idx+=2;
    // line = lines[line_idx];
    // while (line.find("lockers")==std::string::npos){
    //     auto values = split(line, ',');
    //     int idx{std::stoi(values[0])};
    //     float x{std::stof(values[1])};
    //     float y{std::stof(values[2])};
    //     int demand{std::stoi(values[3])};
    //     auto preferred_locker_idxs_str = split(values[4], '-');
    //     std::vector<int> preferred_locker_idxs{};
    //     for (auto& locker_idx_str: preferred_locker_idxs_str){
    //         preferred_locker_idxs.push_back(std::stoi(locker_idx_str));
    //     }
    //     const Coord coord{x,y};
    //     const Customer f_customer{idx, coord, demand, preferred_locker_idxs, true};
    //     nodes.push_back(f_customer);
    //     line_idx++;
    //     line = lines[line_idx];
    // }
    // // read lockers
    // std::map<int, Locker> locker_idx_map;
    // line_idx+=2;
    // line = lines[line_idx];
    // while (line.find("mrt")==std::string::npos){
    //     auto values = split(line, ',');
    //     int idx{std::stoi(values[0])};
    //     float x{std::stof(values[1])};
    //     float y{std::stof(values[2])};
    //     int capacity{std::stoi(values[3])};
    //     float cost{std::stof(values[4])};
    //     const Coord coord{x,y};
    //     const Locker locker{idx, coord, capacity, cost};
    //     nodes.push_back(locker);
    //     locker_idx_map[locker.idx] = locker;
    //     line_idx++;
    //     line = lines[line_idx];
    // }
    // // read mrt lines
    // std::vector<Mrt_line> mrt_lines;
    // line_idx+=2;
    // line = lines[line_idx];
    // while (line.find("distance")==std::string::npos){
    //     auto values = split(line, ',');
    //     int start_station_idx{std::stoi(values[0])};
    //     int end_station_idx{std::stoi(values[1])};
    //     int capacity{std::stoi(values[2])};
    //     float cost{std::stof(values[3])};
    //     Locker start_station{locker_idx_map[start_station_idx]};
    //     Locker end_station{locker_idx_map[end_station_idx]};
    //     const Mrt_line mrt_line{start_station, end_station, capacity, cost};
    //     mrt_lines.push_back(mrt_line);
    //     line_idx++;
    //     line = lines[line_idx];
    // }
    // // read distance matrix
    // line_idx ++;
    // const std::size_t num_nodes{nodes.size()};
    // std::vector<std::vector<float>> distance_matrix(num_nodes);
    // for (int i=0; i<num_nodes;i++){
    //     line_idx ++;
    //     line = lines[line_idx];
    //     auto values = split(line, ',');
    //     for (int j=0;j<num_nodes;j++){
    //         distance_matrix[i].push_back(std::stof(values[j+1]));
    //     }
    // }

    // return 0;
}