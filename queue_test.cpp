#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

#include "queue.h"

using namespace ::testing;

template<typename T>
std::vector<T> drain(Queue<T>& q) {
  std::vector<T> elements{};
  while (!q.empty()) {
    elements.push_back(q.front());
    q.dequeue();
  }
  return elements;
}

TEST(Queue, BasicResize) {
  Queue<int> q(4);
  for (int i = 0; i < 10; i++) {
    q.enqueue(i);
  }
  ASSERT_THAT(drain(q), ElementsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
}

TEST(Queue, WrapAround) {
  std::vector<int> elements{};
  Queue<int> q(4);
  for (int i = 0; i < 10; i++) {
    q.enqueue(i);
    elements.push_back(q.front());
    q.dequeue();
  }
  ASSERT_THAT(elements, ElementsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
}

TEST(Queue, WrapAroundResize) {
  Queue<int> q(4);
  for (int i = 0; i < 3; i++) {
    q.enqueue(i);
    q.dequeue();
  }
  for (int i = 6; i < 20; i++) {
    q.enqueue(i);
  }
  ASSERT_THAT(drain(q), ElementsAre(6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19));
}

TEST(Queue, Front) {
  Queue<int> q(4);
  q.enqueue(1234);
  for (int i = 0; i < 10; i++) {
    q.enqueue(i);
    ASSERT_EQ(q.front(), 1234);
  }
}