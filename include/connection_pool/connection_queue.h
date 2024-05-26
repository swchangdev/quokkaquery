#ifndef QQ_CP_CONNECTION_POOL_H_
#define QQ_CP_CONNECTION_POOL_H_

#include <deque>
#include <future>
#include <memory>

#include "connection_desc.h"

namespace quokkaquery {
namespace cp {
class Connection;
class ConnectionQueue {
 public:
  struct Entry;

  using QueueType = std::deque<std::unique_ptr<Entry>>;
  using Iterator = QueueType::iterator;
  using ConstIterator = QueueType::const_iterator;

  ConnectionQueue() = default;
  ~ConnectionQueue() = default;

  const bool Empty() const;
  const std::size_t Size() const;

  Iterator Insert(std::unique_ptr<Entry>);
  void Pop(ConstIterator);

  Iterator begin();
  ConstIterator begin() const;
  ConstIterator cbegin() const;

  Iterator end();
  ConstIterator end() const;
  ConstIterator cend() const;

 private:
  QueueType list_;
};

struct ConnectionQueue::Entry {
  const ConnectionDesc conn_desc;
  const std::size_t conn_map_idx;
  std::shared_ptr<Connection> conn_ptr;
  std::future<void> worker_handle;

  Entry(const ConnectionDesc& desc, const std::size_t conn_map_idx,
        std::shared_ptr<Connection> conn_ptr, std::future<void>&& handle)
   : conn_desc(desc),
     conn_map_idx(conn_map_idx),
     conn_ptr(conn_ptr),
     worker_handle(std::move(handle)) {}
};
}  // namespace cp
}  // namespace quokkaquery

#endif /* QQ_CP_CONNECTION_QUEUE_H_ */