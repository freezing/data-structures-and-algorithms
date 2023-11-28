#include <iostream>
#include <cassert>
#include <optional>
#include <vector>

#include "lcs.h"

void print_differences(const std::vector<std::string> &file_a,
                       const std::vector<std::string> &file_b) {
  auto lcs = reconstruct_elements(lcs_table(file_a, file_b), file_a, file_b);

  int line_a = 0, line_b = 0;
  for (const auto &line : lcs) {
    while (file_a[line_a] != line) {
      std::cout << "- " << file_a[line_a] << "\n";
      ++line_a;
    }
    while (file_b[line_b] != line) {
      std::cout << "+ " << file_b[line_b] << "\n";
      ++line_b;
    }

    assert(file_a[line_a] == file_b[line_b]);
    std::cout << "  " << file_a[line_a] << "\n";
    ++line_a;
    ++line_b;
  }

  while (line_a < file_a.size()) {
    std::cout << "- " << file_a[line_a] << "\n";
    ++line_a;
  }

  while (line_b < file_b.size()) {
    std::cout << "+ " << file_b[line_b] << "\n";
    ++line_b;
  }
}