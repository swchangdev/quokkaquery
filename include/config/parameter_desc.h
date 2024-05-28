#ifndef QQ_CONFIG_PARAMETER_DESC_H_
#define QQ_CONFIG_PARAMETER_DESC_H_

#include <string> /* for std::string */

namespace quokkaquery {
namespace config {
struct ParameterDesc {
  const std::string category;
  const std::string name;
};
}  // namespace config
}  // namespace quokkaquery

namespace std {
template <>
struct hash<quokkaquery::config::ParameterDesc> {
  using T = quokkaquery::config::ParameterDesc;
  std::size_t operator()(const T& key) const {
    return (std::hash<std::string>()(key.category) ^
            std::hash<std::string>()(key.name) << 1);
  }
};

template <>
struct equal_to<quokkaquery::config::ParameterDesc> {
  using T = quokkaquery::config::ParameterDesc;
  bool operator()(const T& lhs, const T& rhs) const {
    return (lhs.category.compare(rhs.category) == 0) &&
           (lhs.name.compare(lhs.name) == 0);
  }
};
}  // namespace std
#endif /* QQ_CONFIG_PARAMETER_DESC_H_ */