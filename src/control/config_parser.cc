#if FOR_HISTORY
#include "config_parser.h"
#include "config.h"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace ctrl {
ConfigParser::ConfigParser(std::string input_path) {
  auto path = std::filesystem::weakly_canonical(input_path).string();
  config_file_ = common::Config(toml::parse_file(path));
}

const common::Config& ConfigParser::GetConfig() const {
  return config_file_;
}
}  // namespace ctrl
#endif