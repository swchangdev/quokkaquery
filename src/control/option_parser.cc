#include "option_parser.h"

#include <iostream>
#include <vector>
#include <stdexcept>

namespace ctrl {
OptionParser::OptionParser(int argc, char **argv)
 : OptionParser::OptionParser(argc, const_cast<const char **>(argv)) {}

OptionParser::OptionParser(int argc, const char **argv)
 : allowed_options_("Allowed options") {
  allowed_options_.add_options()
    ("help,h", "produce help message")
    ("version,v", "print version")
    ("config-path,f", po::value<std::string>(), "path to config file")
  ;

  po::store(po::parse_command_line(argc, argv, allowed_options_), variables_map_);
  po::notify(variables_map_);
}

const bool OptionParser::ContainsOption(std::string &&key) const {
  return variables_map_.count(std::forward<std::string>(key)) != 0;
}

const po::options_description& OptionParser::GetAllowedOptions() const {
  return allowed_options_;
}
}  // namespace ctrl