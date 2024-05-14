#ifndef QQ_CONNECTION_CONNECTION_DESC_H_
#define QQ_CONNECTION_CONNECTION_DESC_H_

#include <string>

namespace conn {
struct ConnectionDesc {
  const std::string dbname;
  const std::string username;
  const std::string parameter; /* name=value[&...] */

  ConnectionDesc(const std::string& dbname, const std::string& username,
                 const std::string& parameter)
   : dbname(dbname), username(username), parameter(parameter) {}

  ConnectionDesc(const ConnectionDesc& other)
   : dbname(other.dbname),
     username(other.username),
     parameter(other.parameter) {}

  bool operator==(const ConnectionDesc& rhs) const {
    return (dbname == rhs.dbname) && (username == rhs.username) &&
           (parameter == rhs.parameter);
  }
};
}  // namespace conn

namespace std {
template <>
struct hash<conn::ConnectionDesc> {
  std::size_t operator()(const conn::ConnectionDesc& key) const {
    return (std::hash<std::string>()(key.dbname)) ^
           (std::hash<std::string>()(key.username) << 1) ^
           (std::hash<std::string>()(key.parameter) << 2);
  }
};
}  // namespace std
#endif /* QQ_CONNECTION_CONNECTION_DESC_H_ */