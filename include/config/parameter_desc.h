#ifndef CONFIG_PARAMETER_DESC_H_
#define CONFIG_PARAMETER_DESC_H_

#include <string> /* for std::string */

namespace config {
struct ParameterDescriptor {
  const std::string category;
  const std::string name;
  bool operator==(const ParameterDescriptor& rhs) const {
    return (category == rhs.category) && (name == rhs.name);
  }
};
}  // namespace config

namespace std {
template <>
struct hash<config::ParameterDescriptor> {
  std::size_t operator()(const config::ParameterDescriptor& key) const {
    return (std::hash<std::string>()(key.category) ^
            std::hash<std::string>()(key.name) << 1);
  }
};
}  // namespace std
#endif /* CONFIG_PARAMETER_DESC_H_ */