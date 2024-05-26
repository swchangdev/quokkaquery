#ifndef QQ_CP_CONNECTION_H_
#define QQ_CP_CONNECTION_H_

namespace quokkaquery {
namespace cp {
struct ConnectionDesc;
class ConnectionFactory;

class Connection {
 public:
  ~Connection() = default;

  friend ConnectionFactory;

 private:
  Connection() = default;
  Connection(const Connection&) = delete;
  Connection(Connection&&) = delete;
  Connection& operator=(const Connection&) = delete;

  explicit Connection(const ConnectionDesc&) {}
};
}  // namespace cp
}  // namespace quokkaquery

#endif /* QQ_CP_CONNECTION_H_ */