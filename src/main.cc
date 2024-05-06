#include <cassert>
#include <iostream>
#include <string_view>
#include "control/option_parser.h"
#include "control/version.h"

static inline const bool CheckForImmediateExit(const ctrl::OptionParser &);

int main(int argc, char **argv) {
  ctrl::OptionParser option_parser(argc, argv);

  if (CheckForImmediateExit(option_parser)) {
    exit(EXIT_SUCCESS);
  }

  exit(EXIT_SUCCESS);
}

static inline const bool CheckForImmediateExit(const ctrl::OptionParser &option_parser) {
  bool immediate_exit = false;

  if (option_parser.ContainsOption("help")) {
    const auto &allowed_options = option_parser.GetAllowedOptions();
    std::cout << allowed_options << std::endl;
    immediate_exit = true;
  } else if (option_parser.ContainsOption("version")) {
    std::cout << "QuokkaQuery " << ctrl::GetCurrentVersion() << std::endl;
    immediate_exit = true;
  }

  return immediate_exit;
}
