#ifndef QQ_PROTOCOL_CONNECTION_POOL_H_
#define QQ_PROTOCOL_CONNECTION_POOL_H_

#include <deque>         /* for std::deque */
#include <memory>        /* for std::shared_ptr */
#include <unordered_map> /* for std::unordered_map */
#include <vector>        /* for std::vector */

#include "connection_desc.h"
#include "connection_handle.h"

namespace quokkaquery {
namespace protocol {
class ConnectionPool {
 public:
  using ConnectionHandlePtr = std::shared_ptr<ConnectionHandle>;
  using ConnectionHandlePtrs = std::vector<ConnectionHandlePtr>;
  using Map = std::unordered_map<ConnectionDesc, ConnectionHandlePtrs>;
  using Queue = std::deque<ConnectionHandlePtr>;

  explicit ConnectionPool(std::size_t pool_size);
  ~ConnectionPool();

  const bool Empty() const;
  const std::size_t Size() const;
  const std::size_t Capability() const;

  void Resize(std::size_t new_size);

  ConnectionHandlePtr Emplace(const ConnectionDesc&);
  ConnectionHandlePtr Reuse(const ConnectionDesc&);
  ConnectionHandlePtr ReuseOrEmplace(const ConnectionDesc&);
  ConnectionHandlePtr Get(ConnectionHandle::Locator);

  void Invalidate(const ConnectionHandle::Locator&);
  void Invalidate(const ConnectionDesc&);
  void Invalidate();

 private:
  void InvalidateLRU();
  ConnectionHandlePtr EmplaceInternal(const ConnectionDesc&, const std::size_t npos);

  Map map_;
  Queue lru_list_;
  std::size_t size_;
  std::size_t capability_;
};
}  // namespace protocol
}  // namespace quokkaquery

#endif /* QQ_PROTOCOL_CONNECTION_MAP_H_ */