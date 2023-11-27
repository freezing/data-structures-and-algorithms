#include <iostream>
#include <vector>

#include "lcs.h"

// TODO: Construct differences into a struct, so I can test it.

struct Differences {
  std::vector<int> removed_lines_a;
  std::vector<int> added_lines_b;

  bool operator<=>(const Differences &) const = default;
};

Differences compute_differences(const std::vector<std::string> &file_a,
                                const std::vector<std::string> &file_b,
                                const std::vector<std::string> &lcs) {
  Differences differences{};
  int line_a = 0, line_b = 0;
  for (const auto &line : lcs) {
    while (file_a[line_a] != line) {
      differences.removed_lines_a.push_back(line_a);
      ++line_a;
    }
    while (file_b[line_b] != line) {
      differences.added_lines_b.push_back(line_b);
      ++line_b;
    }
    ++line_a;
    ++line_b;
  }

  // Print any remaining lines
  while (line_a < file_a.size()) {
    differences.removed_lines_a.push_back(line_a);
    ++line_a;
  }

  while (line_b < file_b.size()) {
    differences.added_lines_b.push_back(line_b);
    ++line_b;
  }
  return differences;
}

void print_differences(const Differences &differences,
                       const std::vector<std::string> &file_a,
                       const std::vector<std::string> &file_b) {
  for (const auto &line : differences.removed_lines_a) {
    std::cout << "Remove line " << line + 1 << ": " << file_a[line]
              << std::endl;
  }
  for (const auto &line : differences.added_lines_b) {
    std::cout << "Add line " << line + 1 << ": " << file_b[line] << std::endl;
  }
}

Differences lcs_diff(const std::vector<std::string> &file_a,
                     const std::vector<std::string> &file_b) {
  auto dp_table = lcs_table(file_a, file_b);
  auto lcs = reconstruct_elements(dp_table, file_a, file_b);
  return compute_differences(file_a, file_b, lcs);
}

void print_diff(const std::vector<std::string> &file_a,
                const std::vector<std::string> &file_b) {
  auto differences = lcs_diff(file_a, file_b);
  print_differences(differences, file_a, file_b);
}