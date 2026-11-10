#pragma once

#include <map>
#include <string>

// results[fileName][functionName] = time complexity text, e.g. "O(n)"
using ComplexityResults =
    std::map<std::string, std::map<std::string, std::string>>;

// Prints the Time Complexity Calculator report for every file and function.
void printReport(const ComplexityResults &results);
