#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

#include "text_diff.h"

using namespace ::testing;

inline void PrintTo(const Differences &differences, std::ostream *os) {
  *os << "Differences{";
  *os << "removed_lines_a: ";
  *os << PrintToString(differences.removed_lines_a);
  *os << ", added_lines_b: ";
  *os << PrintToString(differences.added_lines_b);
  *os << "}";
}

TEST(TextDiff, Basic) {
  std::vector<std::string> file_a = {"Hello",
                                     "World",
                                     "This",
                                     "Is",
                                     "File",
                                     "A"};
  std::vector<std::string> file_b = {"Hello",
                                     "This",
                                     "File",
                                     "B",
                                     "Is",
                                     "World"};
  Differences expected{
      .removed_lines_a = {1, 3, 5},
      .added_lines_b = {3, 4, 5},
  };
  ASSERT_THAT(lcs_diff(file_a, file_b), Eq(expected));
}