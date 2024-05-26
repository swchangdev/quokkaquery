#ifndef QQ_CP_CONNECTION_FACTORY_H_
#define QQ_CP_CONNECTION_FACTORY_H_

#include <memory>

namespace quokkaquery {
namespace cp {
class Connection;
struct ConnectionDesc;

class ConnectionFactory {
 public:
  ConnectionFactory() = default;
  ConnectionFactory(const ConnectionFactory&) = delete;
  ConnectionFactory(ConnectionFactory&&) = delete;
  ~ConnectionFactory() = default;

  static std::shared_ptr<Connection> GetConnection(const ConnectionDesc& conn_desc);
  static std::shared_ptr<Connection> GetInvalidConnection();
};
}  // namespace cp
}  // namespace quokkaquery

#endif /* QQ_CP_CONNECTION_FACTORY_H_ */
