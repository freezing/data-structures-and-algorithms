#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

#include "closed_addressing_hash_map.h"

using namespace ::testing;

const std::string kTechWithNikola = "techwithnikola";

TEST(ClosedAddressingHashMap, Basic) {
  ClosedAddressingHashMap<std::string, int> map(10);

  ASSERT_THAT(map, IsEmpty());

  map.insert(kTechWithNikola, 1);
  ASSERT_EQ(map.get(kTechWithNikola), 1);

  ASSERT_EQ(map.contains("test"), false);
  map.insert("test", 5);
  ASSERT_EQ(map.contains("test"), true);
  ASSERT_EQ(map.get(kTechWithNikola), 1);
  ASSERT_EQ(map.get("test"), 5);

  ASSERT_EQ(map.contains(kTechWithNikola), true);
  map.remove(kTechWithNikola);
  ASSERT_EQ(map.contains(kTechWithNikola), false);
}

TEST(ClosedAddressingHashMap, Rehashing) {
  ClosedAddressingHashMap<std::string, int> map(4);
  for (int i = 0; i < 100; i++) {
	map.insert(std::to_string(i), i);
  }

  for (int i = 0; i < 100; i++) {
	ASSERT_EQ(map.get(std::to_string(i)), i);
  }

  for (int i = 0; i < 100; i++) {
	map.remove(std::to_string(i));
	for (int j = i + 1; j < 100; j++) {
	  ASSERT_EQ(map.get(std::to_string(j)), j);
	}
  }

  ASSERT_EQ(map.empty(), true);
}