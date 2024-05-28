#include "user_input.h"

#include <filesystem>

namespace quokkaquery {
namespace config {
static inline decltype(auto) GetTomlTbl(const std::string& file_path) {
  auto cann_path = std::filesystem::weakly_canonical(file_path);
  return toml::parse_file(cann_path.string());
}

static inline decltype(auto) GetTomlTbl(std::stringstream& config) {
  return toml::parse(config);
}

UserInput::UserInput(const std::string& file_path)
 : UserInput(std::move(GetTomlTbl(file_path))) {}

UserInput::UserInput(std::stringstream& config)
 : UserInput(std::move(GetTomlTbl(config))) {}

UserInput::UserInput(toml::table&& toml_tbl)
 : toml_tbl_(std::move(toml_tbl)) {
  for (auto& iter : toml_tbl_) {
    std::string table_name{iter.first.str()};
    const auto table = iter.second.as_table();

    for (auto& kv : *table) {
      std::string key_name{kv.first.str()};
      ParameterDesc param_desc{table_name, key_name};
      toml::node_view<const toml::node> node(kv.second);
      config_tbl_.insert(std::make_pair(std::move(param_desc), std::move(node)));
    }
  }
}

UserInput::Iterator UserInput::begin() noexcept {
  return config_tbl_.begin();
}

UserInput::ConstIterator UserInput::begin() const noexcept {
  return config_tbl_.begin();
}

UserInput::ConstIterator UserInput::cbegin() const noexcept {
  return config_tbl_.cbegin();
}

UserInput::Iterator UserInput::end() noexcept {
  return config_tbl_.end();
}

UserInput::ConstIterator UserInput::end() const noexcept {
  return config_tbl_.end();
}

UserInput::ConstIterator UserInput::cend() const noexcept {
  return config_tbl_.cend();
}

}  // namespace config
}  // namespace quokkaquery