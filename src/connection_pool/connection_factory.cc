#include "connection_factory.h"

#include "connection.h"
#include "connection_desc.h"

namespace quokkaquery {
namespace cp {
std::shared_ptr<Connection> ConnectionFactory::GetConnection(const ConnectionDesc& conn_desc) {
  auto conn_ptr = new Connection(conn_desc);
  return std::shared_ptr<Connection>(conn_ptr);
}

std::shared_ptr<Connection> ConnectionFactory::GetInvalidConnection() {
  return std::shared_ptr<Connection>(nullptr);
}
}  // namespace cp
}  // namespace quokkaquery