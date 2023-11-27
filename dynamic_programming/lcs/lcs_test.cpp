#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

#include "lcs.h"

using namespace ::testing;

TEST(Lcs, Basic) {
  std::vector<int> a{6, 4, 5, 9, 11};
  std::vector<int> b{1, 15, 4, 5, 6, 9, 10, 11};
  int lcs = longest_common_subsequence(a, b);
  ASSERT_THAT(lcs, Eq(4));
}

TEST(Lcs, Empty) {
  std::vector<int> a{};
  std::vector<int> b{1, 15, 4, 5, 6, 9, 10, 11};
  int lcs = longest_common_subsequence(a, b);
  ASSERT_THAT(lcs, Eq(0));
}

TEST(Lcs, EmptyBoth) {
  std::vector<int> a{};
  std::vector<int> b{};
  int lcs = longest_common_subsequence(a, b);
  ASSERT_THAT(lcs, Eq(0));
}

TEST(Lcs, Same) {
  std::vector<int> a{1, 2, 3, 4, 5};
  std::vector<int> b{1, 2, 3, 4, 5};
  int lcs = longest_common_subsequence(a, b);
  ASSERT_THAT(lcs, Eq(5));
}

TEST(ReconstructLcs, Basic) {
  std::vector<int> a{6, 4, 5, 9, 11};
  std::vector<int> b{1, 15, 4, 5, 6, 9, 10, 11};
  auto lcs = lcs_table(a, b);
  std::vector<int> elements = reconstruct_elements(lcs, a, b);
  ASSERT_THAT(elements, ElementsAre(4, 5, 9, 11));
}

TEST(ReconstructLcs, Empty) {
  std::vector<int> a{};
  std::vector<int> b{1, 15, 4, 5, 6, 9, 10, 11};
  auto lcs = lcs_table(a, b);
  std::vector<int> elements = reconstruct_elements(lcs, a, b);
  ASSERT_THAT(elements, ElementsAre());
}

TEST(ReconstructLcs, EmptyBoth) {
  std::vector<int> a{};
  std::vector<int> b{};
  auto lcs = lcs_table(a, b);
  std::vector<int> elements = reconstruct_elements(lcs, a, b);
  ASSERT_THAT(elements, ElementsAre());
}

TEST(ReconstructLcs, Same) {
  std::vector<int> a{1, 2, 3, 4, 5};
  std::vector<int> b{1, 2, 3, 4, 5};
  auto lcs = lcs_table(a, b);
  std::vector<int> elements = reconstruct_elements(lcs, a, b);
  ASSERT_THAT(elements, ElementsAre(1, 2, 3, 4, 5));
}