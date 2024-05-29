#ifndef QQ_PROTOCOL_CONNECTION_HANDLE_H_
#define QQ_PROTOCOL_CONNECTION_HANDLE_H_

#include <future> /* for std::future */
#include <memory> /* for std::unique_ptr */
#include <vector> /* for std::vector */

#include "connection.h"

namespace quokkaquery {
namespace protocol {
/* forward declaration */
struct ConnectionDesc;

struct ConnectionHandle {
  struct Locator {
    const ConnectionDesc& conn_desc;
    const std::size_t npos;
  };

  using WorkerHandle = std::unique_ptr<std::future<void>>;
  using UserConnectionPtr = UserConnection::Pointer;
  using DatabaseConnectionPtrs = std::vector<DatabaseConnection::Pointer>;

  ConnectionHandle(const ConnectionDesc& conn_desc, const std::size_t npos)
      : locator{conn_desc, npos},
        worker_handle(nullptr),
        user_connection(nullptr),
        database_connections() {}

  Locator locator;
  WorkerHandle worker_handle;
  UserConnectionPtr user_connection;
  DatabaseConnectionPtrs database_connections;
};
}  // namespace protocol
}  // namespace quokkaquery
#endif /* QQ_PROTOCOL_CONNECTION_HANDLE_H_ */