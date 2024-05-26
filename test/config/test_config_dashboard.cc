#include "dashboard.h"
#include "gtest/gtest.h"

using namespace quokkaquery::config;

TEST(TestConfigDashboard, constructor) {
  Dashboard dashboard;
  EXPECT_TRUE(dashboard.Empty());
}

TEST(TestConfigDashboard, populate) {
  Dashboard dashboard;
  dashboard.Populate();

  EXPECT_FALSE(dashboard.Empty());
}

TEST(TestConfigDashboard, find_true) {
  Dashboard dashboard;
  dashboard.Populate();

  ParameterDesc desc{
    "general",
    "port",
  };
  auto found = dashboard.Find(desc);
  EXPECT_EQ(found->second.type, Parameter::TypeId::RANGE);
  
  const auto param = std::get<RangeParameter>(*found->second.value);
  EXPECT_EQ(param.Get(), 9999);
}

TEST(TestConfigDashboard, find_false) {
  Dashboard dashboard;
  dashboard.Populate();

  ParameterDesc desc{
    "fake_category",
    "fake_name",
  };

  auto found = dashboard.Find(desc);
  EXPECT_EQ(found, dashboard.end());
}

TEST(TestConfigDashboard, update) {
  Dashboard dashboard;
  dashboard.Populate();

  ParameterDesc desc{
    "general",
    "port",
  };
  
  auto first_found = dashboard.Find(desc);
  std::get<RangeParameter>(*first_found->second.value).Set(9998);
  
  const auto& second_found = dashboard.Find(desc);
  EXPECT_EQ(std::get<RangeParameter>(*second_found->second.value).Get(), 9998);
}