#include <iostream>

#include "lcs.h"

void print_matrix(const std::vector<std::vector<int>> &dp) {
    for (const auto &row: dp) {
        for (const auto &elem: row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<int> a{1, 4, 5, 6, 9, 10, 11};
    std::vector<int> b{6, 4, 5, 9, 11};
    auto dp = lcs_table(b, a);
    print_matrix(dp);
    return 0;
}