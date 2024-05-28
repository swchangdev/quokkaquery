#include "connection_pool.h"

#include "connection_desc.h"

namespace quokkaquery {
namespace protocol {
static inline const bool CheckOccupied(ConnectionPool::ConnectionHandlePtr ptr) {
  /* Unoccupied only if it has null worker handle */
  return !ptr && !(ptr->worker_handle);
}

static inline ConnectionPool::ConnectionHandlePtr GetInvalidConnHandlePtr() {
  return ConnectionPool::ConnectionHandlePtr(nullptr);
}

ConnectionPool::ConnectionPool(std::size_t pool_size)
    : map_(pool_size),
      lru_list_(pool_size),
      size_(0),
      capability_(pool_size) {}

ConnectionPool::~ConnectionPool() {
  if (!Empty()) {
    Invalidate();
  }
}

const bool ConnectionPool::Empty() const {
  return size_ == 0;
}

const std::size_t ConnectionPool::Size() const {
  return size_;
}

const std::size_t ConnectionPool::Capability() const {
  return capability_;
}

void ConnectionPool::Resize(std::size_t new_size) {
  map_.rehash(new_size);
  lru_list_.resize(new_size);
  capability_ = new_size;
}

ConnectionPool::ConnectionHandlePtr ConnectionPool::Emplace(const ConnectionDesc& desc) {
  if (size_ == capability_) {
    InvalidateLRU();
  }

  auto iter = map_.find(desc);
  std::size_t npos = iter == map_.end() ? 0 : iter->second.size();

  return EmplaceInternal(desc, npos);
}

ConnectionPool::ConnectionHandlePtr ConnectionPool::Reuse(const ConnectionDesc& desc) {
  auto iter = map_.find(desc);
  if (iter == map_.end()) {
    return GetInvalidConnHandlePtr();
  }

  auto conn_ptr = GetInvalidConnHandlePtr();
  for (auto& conn : iter->second) {
    if (!CheckOccupied(conn)) {
      conn_ptr = conn;
    }
  }

  return conn_ptr;
}

ConnectionPool::ConnectionHandlePtr ConnectionPool::ReuseOrEmplace(const ConnectionDesc& desc) {
  auto iter = map_.find(desc);

  if (iter == map_.end()) {
    return EmplaceInternal(desc, 0);
  }

  return Reuse(desc);
}

ConnectionPool::ConnectionHandlePtr ConnectionPool::Get(ConnectionHandle::Locator loc) {
  auto iter = map_.find(loc.conn_desc);

  if (iter == map_.end()) {
    return GetInvalidConnHandlePtr();
  }

  auto &array = iter->second;
  if (array.size() <= loc.npos) {
    return GetInvalidConnHandlePtr();
  }

  return array[loc.npos];
}

void ConnectionPool::Invalidate(const ConnectionHandle::Locator&) {
  /* TODO QQ-90 */
  return;
}

void ConnectionPool::Invalidate(const ConnectionDesc&) {
  /* TODO QQ-90 */
  return;
}

void ConnectionPool::Invalidate() {
  /* TODO QQ-90 */
  return;
}

void ConnectionPool::InvalidateLRU() {
  /* TODO QQ-90 */
  throw std::exception();
}

ConnectionPool::ConnectionHandlePtr ConnectionPool::EmplaceInternal(const ConnectionDesc& desc,
                                                                    const std::size_t npos) {
  auto& new_entry = map_[desc].emplace_back(std::make_shared<ConnectionHandle>(desc, npos));
  lru_list_.emplace_back(new_entry);
  ++size_;

  return new_entry;
}
}  // namespace protocol
}  // namespace quokkaquery