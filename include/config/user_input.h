#ifndef QQ_CONFIG_USER_INPUT_H_
#define QQ_CONFIG_USER_INPUT_H_

#include <toml++/toml.h> /* for toml library */

#include <sstream>       /* for std::stringstream */
#include <string>        /* for std::string */
#include <unordered_map> /* for std::unordered_map */

#include "parameter_desc.h"

namespace config {
class UserInput {
 public:
  using TableType = std::unordered_map<ParameterDesc, toml::node_view<const toml::node>>;
  using Iterator = TableType::iterator;
  using ConstIterator = TableType::const_iterator;

  explicit UserInput(const std::string& file_path); 
  explicit UserInput(std::stringstream& config);

  ~UserInput() = default;

  Iterator begin() noexcept;
  ConstIterator begin() const noexcept;
  ConstIterator cbegin() const noexcept;

  Iterator end() noexcept;
  ConstIterator end() const noexcept;
  ConstIterator cend() const noexcept;

 private:
  explicit UserInput(toml::table&& toml_tbl);
  toml::table toml_tbl_;
  TableType config_tbl_; 
};
}  // namespace config
#endif /* QQ_CONFIG_USER_INPUT_H_ */