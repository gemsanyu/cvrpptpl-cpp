#ifndef CVRPPTPL_UTILS_H
#define CVRPPTPL_UTILS_H

#include <iterator>
#include <string>
#include <sstream>
#include <vector>

template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim);

#endif