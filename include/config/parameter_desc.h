#ifndef QQ_CONFIG_PARAMETER_DESC_H_
#define QQ_CONFIG_PARAMETER_DESC_H_

#include <string> /* for std::string */

namespace config {
struct ParameterDesc {
  const std::string category;
  const std::string name;
  bool operator==(const ParameterDesc& rhs) const {
    return (category == rhs.category) && (name == rhs.name);
  }
};
}  // namespace config

namespace std {
template <>
struct hash<config::ParameterDesc> {
  std::size_t operator()(const config::ParameterDesc& key) const {
    return (std::hash<std::string>()(key.category) ^
            std::hash<std::string>()(key.name) << 1);
  }
};
}  // namespace std
#endif /* QQ_CONFIG_PARAMETER_DESC_H_ */