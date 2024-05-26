#include <gtest/gtest.h>
#include "user_input.h"

using namespace quokkaquery::config;
TEST(TestConfigUserInput, constructor) {
  std::string_view sv = R"(
    [test]
    key = "value"
  )";

  std::stringstream ss{ std::string{ sv } };
  UserInput user_input(ss);

  const auto iter = user_input.begin();
  const auto& key = iter->first;
  const auto& value = iter->second;

  EXPECT_EQ(key.category, "test");
  EXPECT_EQ(key.name, "key");
  EXPECT_EQ(value.value_or<std::string>("").compare("value"), 0);
}

std::string_view sv = R"(
  [a]
  k1 = "v1"
  k2 = "v2"

  [b]
  k1 = "v1"
  k2 = "v2"
  k3 = "v3"
)";

TEST(TestConfigUserInput, for_loop) {
  std::stringstream ss{std::string{sv}};
  UserInput user_input(ss);
  std::unordered_map<std::string, int> hit_count;
  std::unordered_map<std::string, std::string> values;

  auto iter = user_input.begin();
  for (; iter != user_input.end(); ++iter) {
    auto category = iter->first.category;
    auto name = iter->first.name;
    auto& node = iter->second;

    ++hit_count[category];
    ++hit_count[name];
    values[category + name] = node.value_or("");
  }

  EXPECT_EQ(hit_count["a"], 2);
  EXPECT_EQ(hit_count["b"], 3);
  EXPECT_EQ(hit_count["k1"], 2);
  EXPECT_EQ(hit_count["k2"], 2);
  EXPECT_EQ(hit_count["k3"], 1);

  EXPECT_EQ(values["ak1"].compare("v1"), 0);
  EXPECT_EQ(values["ak2"].compare("v2"), 0);
  EXPECT_EQ(values["bk1"].compare("v1"), 0);
  EXPECT_EQ(values["bk2"].compare("v2"), 0);
  EXPECT_EQ(values["bk3"].compare("v3"), 0);
}

TEST(TestConfigUserInput, for_each) {
  std::stringstream ss{std::string{sv}};
  UserInput user_input(ss);
  std::unordered_map<std::string, int> hit_count;
  std::unordered_map<std::string, std::string> values;

  for (auto& iter : user_input) {
    auto category = iter.first.category;
    auto name = iter.first.name;
    auto& node = iter.second;

    ++hit_count[category];
    ++hit_count[name];
    values[category + name] = node.value_or("");
  }

  EXPECT_EQ(hit_count["a"], 2);
  EXPECT_EQ(hit_count["b"], 3);
  EXPECT_EQ(hit_count["k1"], 2);
  EXPECT_EQ(hit_count["k2"], 2);
  EXPECT_EQ(hit_count["k3"], 1);

  EXPECT_EQ(values["ak1"].compare("v1"), 0);
  EXPECT_EQ(values["ak2"].compare("v2"), 0);
  EXPECT_EQ(values["bk1"].compare("v1"), 0);
  EXPECT_EQ(values["bk2"].compare("v2"), 0);
  EXPECT_EQ(values["bk3"].compare("v3"), 0);
}