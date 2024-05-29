#ifndef QQ_PROTOCOL_CONNECTION_POOL_H_
#define QQ_PROTOCOL_CONNECTION_POOL_H_

#include <list>          /* for std::list */
#include <memory>        /* for std::shared_ptr */
#include <unordered_map> /* for std::unordered_map */
#include <utility>       /* for std::pair */
#include <vector>        /* for std::vector */

#include "connection_desc.h"
#include "connection_handle.h"

namespace quokkaquery {
namespace protocol {
class ConnectionPool {
 public:
  using ConnectionHandlePtr = std::shared_ptr<ConnectionHandle>;
  using List = std::list<ConnectionHandlePtr>;
  using MapValue = std::pair<std::vector<List::iterator>, std::size_t>;
  using Map = std::unordered_map<ConnectionDesc, MapValue>;

  explicit ConnectionPool(std::size_t pool_size);
  ~ConnectionPool();

  const bool Empty() const;
  const std::size_t Size() const;
  const std::size_t Capability() const;

  void Resize(std::size_t new_size);

  ConnectionHandlePtr Emplace(const ConnectionDesc&);
  ConnectionHandlePtr Reuse(const ConnectionDesc&);

  void Invalidate();

 private:
  bool Contains(const ConnectionDesc&);
  void EmplaceEmptyContainer(const ConnectionDesc&);
  const std::size_t GetAvailableSlot(const ConnectionDesc&);

  ConnectionHandlePtr EmplaceInternal(const ConnectionDesc&, const std::size_t);
  ConnectionHandlePtr ReuseInternal(const ConnectionDesc&);
  
  void InvalidateLRU();
  void InvalidateInternal(ConnectionHandle::Locator);

  Map map_;
  List lru_list_;
  std::size_t size_;
  std::size_t capability_;
};
}  // namespace protocol
}  // namespace quokkaquery

#endif /* QQ_PROTOCOL_CONNECTION_MAP_H_ */