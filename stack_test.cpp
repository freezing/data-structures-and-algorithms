#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

#include "stack.h"

using namespace ::testing;

template<typename T>
std::vector<T> drain(Stack<T>& s) {
  std::vector<T> elements{};
  while (!s.empty()) {
    elements.push_back(s.top());
    s.pop();
  }
  return elements;
}

TEST(Stack, ChangeCapacity) {
  Stack<int> s(4);
  for (int i = 0; i < 10; i++) {
    s.push(i);
  }

  ASSERT_THAT(drain(s), ElementsAre(9, 8, 7, 6, 5, 4, 3, 2, 1, 0));
}

TEST(Stack, Top) {
  Stack<int> s(4);
  for (int i = 0; i < 10; i++) {
    s.push(i);
    ASSERT_EQ(s.top(), i);
  }
}