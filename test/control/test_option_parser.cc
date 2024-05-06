#include "option_parser.h"
#include "gtest/gtest.h"

TEST(OptionParserTest, help) {
  int argc = 2;
  const char *argv[] = {"quokkaquery", "--help"};

  ctrl::OptionParser option_parser(argc, argv);
  EXPECT_TRUE(option_parser.ContainsOption("help"));
}

TEST(OptionParserTest, help_short) {
  int argc = 2;
  const char *argv[] = {"quokkaquery", "-h"};

  ctrl::OptionParser option_parser(argc, argv);
  EXPECT_TRUE(option_parser.ContainsOption("help"));
}

TEST(OptionParserTest, version) {
  int argc = 2;
  const char *argv[] = {"quokkaquery", "--version"};

  ctrl::OptionParser option_parser(argc, argv);
  EXPECT_TRUE(option_parser.ContainsOption("version"));
}

TEST(OptionParserTest, version_short) {
  int argc = 2;
  const char *argv[] = {"quokkaquery", "-v"};

  ctrl::OptionParser option_parser(argc, argv);
  EXPECT_TRUE(option_parser.ContainsOption("version"));
}

TEST(OptionParserTest, config_path) {
  int argc = 3;
  const char *argv[] = {"quokkaquery", "--config-path", "/test/path"};

  ctrl::OptionParser option_parser(argc, argv);
  EXPECT_EQ(option_parser.GetOptionValue<std::string>("config-path").compare("/test/path"), 0);
}

TEST(OptionParserTest, config_path_short) {
  int argc = 3;
  const char *argv[] = {"quokkaquery", "-f", "/test/path"};

  ctrl::OptionParser option_parser(argc, argv);
  EXPECT_EQ(option_parser.GetOptionValue<std::string>("config-path").compare("/test/path"), 0);
}
