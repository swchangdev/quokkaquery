#ifndef QQ_CONNECTION_CONNECTION_H_
#define QQ_CONNECTION_CONNECTION_H_

namespace conn {
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

}  // namespace conn
#endif /* QQ_CONNECTION_CONNECTION_H_ */