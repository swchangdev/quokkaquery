#ifndef QQ_CP_CONNECTION_DESC_H_
#define QQ_CP_CONNECTION_DESC_H_

#include <string>

namespace quokkaquery {
namespace cp {
struct ConnectionDesc {
  const std::string dbname;
  const std::string username;
  const std::string parameter; /* name=value[&...] */
};

}  // namespace cp
}  // namespace quokkaquery

namespace std {
template <>
struct hash<quokkaquery::cp::ConnectionDesc> {
  using T = quokkaquery::cp::ConnectionDesc;
  std::size_t operator()(const T& key) const {
    return (std::hash<std::string>()(key.dbname)) ^
           (std::hash<std::string>()(key.username) << 1) ^
           (std::hash<std::string>()(key.parameter) << 2);
  }
};

template <>
struct equal_to<quokkaquery::cp::ConnectionDesc> {
  using T = quokkaquery::cp::ConnectionDesc;
  bool operator()(const T& lhs, const T& rhs) const {
    return (lhs.dbname.compare(rhs.dbname) == 0) &&
           (lhs.username.compare(rhs.username) == 0) &&
           (lhs.parameter.compare(rhs.parameter) == 0);
  }
};
}  // namespace std

#endif /* QQ_CP_CONNECTION_DESC_H_ */