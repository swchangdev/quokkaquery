#include "dashboard.h"
#include "gtest/gtest.h"

TEST(TestConfigDashboard, constructor) {
  config::Dashboard dashboard;
  EXPECT_TRUE(dashboard.Empty());
}

TEST(TestConfigDashboard, populate) {
  config::Dashboard dashboard;
  dashboard.Populate();

  EXPECT_FALSE(dashboard.Empty());
}

TEST(TestConfigDashboard, find_true) {
  config::Dashboard dashboard;
  dashboard.Populate();

  config::ParameterDesc desc{
    "general",
    "port",
  };
  auto found = dashboard.Find(desc);
  EXPECT_EQ(found->second.type, config::Parameter::TypeId::RANGE);
  
  const auto param = std::get<config::RangeParameter>(*found->second.value);
  EXPECT_EQ(param.Get(), 9999);
}

TEST(TestConfigDashboard, find_false) {
  config::Dashboard dashboard;
  dashboard.Populate();

  config::ParameterDesc desc{
    "fake_category",
    "fake_name",
  };

  auto found = dashboard.Find(desc);
  EXPECT_EQ(found, dashboard.end());
}

TEST(TestConfigDashboard, update) {
  config::Dashboard dashboard;
  dashboard.Populate();

  config::ParameterDesc desc{
    "general",
    "port",
  };
  
  auto first_found = dashboard.Find(desc);
  std::get<config::RangeParameter>(*first_found->second.value).Set(9998);
  
  const auto& second_found = dashboard.Find(desc);
  EXPECT_EQ(std::get<config::RangeParameter>(*second_found->second.value).Get(), 9998);
}