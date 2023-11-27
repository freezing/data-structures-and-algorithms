#pragma once

#include <vector>

std::vector<std::vector<int>> lcs_table(const std::vector<int> &a,
                                        const std::vector<int> &b) {
  std::vector<std::vector<int>> dp(a.size() + 1,
                                   std::vector<int>(b.size() + 1, 0));
  for (int i = 1; i <= a.size(); i++) {
    for (int j = 1; j <= b.size(); j++) {
      if (a[i - 1] == b[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  return dp;
}

int longest_common_subsequence(const std::vector<int> &a,
                               const std::vector<int> &b) {
  return lcs_table(a, b)[a.size()][b.size()];
}

std::vector<int> reconstruct_elements(const std::vector<std::vector<int>> &dp,
                                      const std::vector<int> &a,
                                      const std::vector<int> &b) {
  std::vector<int> elements{};
  int n = a.size();
  int m = b.size();
  while (n > 0 && m > 0) {
    if (a[n - 1] == b[m - 1]) {
      elements.push_back(a[n - 1]);
      n--;
      m--;
    } else if (dp[n - 1][m] > dp[n][m - 1]) {
      n--;
    } else {
      m--;
    }
  }
  std::reverse(elements.begin(), elements.end());
  return elements;
}