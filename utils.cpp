#include "utils.h"
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}