#include "Report.h"

#include <iostream>

void printReport(const ComplexityResults &results) {
  std::size_t functionCount = 0;

  std::cout << "### Time Complexity Calculator ###\n";
  for (const auto &[fileName, functions] : results) {
    std::cout << fileName << "\n";
    for (const auto &[functionName, complexity] : functions) {
      std::cout << "- " << functionName << ": " << complexity << "\n";
      ++functionCount;
    }
  }

  std::cout << "\nFiles Analyzed: " << results.size() << "\n"
            << "Functions Analyzed: " << functionCount << std::endl;
}
