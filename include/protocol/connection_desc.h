#ifndef QQ_PROTOCOL_CONNECTION_DESC_H_
#define QQ_PROTOCOL_CONNECTION_DESC_H_

#include <string> /* for std::string */

namespace quokkaquery {
namespace protocol {
struct ConnectionDesc {
  const std::string dbname;
  const std::string username;
  const std::string parameter; /* name=value[&...] */
};

}  // namespace protocol
}  // namespace quokkaquery

namespace std {
template <>
struct hash<quokkaquery::protocol::ConnectionDesc> {
  using T = quokkaquery::protocol::ConnectionDesc;
  std::size_t operator()(const T& key) const {
    return (std::hash<std::string>()(key.dbname)) ^
           (std::hash<std::string>()(key.username) << 1) ^
           (std::hash<std::string>()(key.parameter) << 2);
  }
};

template <>
struct equal_to<quokkaquery::protocol::ConnectionDesc> {
  using T = quokkaquery::protocol::ConnectionDesc;
  bool operator()(const T& lhs, const T& rhs) const {
    return (lhs.dbname.compare(rhs.dbname) == 0) &&
           (lhs.username.compare(rhs.username) == 0) &&
           (lhs.parameter.compare(rhs.parameter) == 0);
  }
};
}  // namespace std

#endif /* QQ_PROTOCOL_CONNECTION_DESC_H_ */