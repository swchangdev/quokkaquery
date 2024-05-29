#include "connection_pool.h"

#include <cassert>
#include "connection_desc.h"

namespace quokkaquery {
namespace protocol {
using ConnectionHandlePtr = ConnectionPool::ConnectionHandlePtr;
using ConnectionMap = ConnectionPool::Map;
using ConnectionList = ConnectionPool::List;

static inline const bool CheckOccupied(ConnectionHandlePtr& ptr) {
  /* Unoccupied only if it has null worker handle */
  return !ptr && !(ptr->worker_handle);
}

static inline ConnectionHandlePtr InvalidConnHandlePtr() {
  return ConnectionHandlePtr(nullptr);
}

static inline std::vector<ConnectionList::iterator>& Array(ConnectionMap::iterator iter) {
  return iter->second.first;
}

static inline std::size_t& RealArraySize(ConnectionPool::Map::iterator iter) {
  return iter->second.second;
}

ConnectionPool::ConnectionPool(std::size_t pool_size)
    : map_(pool_size),
      lru_list_(),
      size_(0),
      capability_(pool_size) {}

ConnectionPool::~ConnectionPool() {
  if (!Empty()) {
    Invalidate();
  }
}

const bool ConnectionPool::Empty() const {
  return map_.empty();
}

const std::size_t ConnectionPool::Size() const {
  return size_;
}

const std::size_t ConnectionPool::Capability() const {
  return capability_;
}

void ConnectionPool::Resize(std::size_t new_size) {
  map_.rehash(new_size);
  capability_ = new_size;
}

ConnectionHandlePtr ConnectionPool::Emplace(const ConnectionDesc& desc) {
  if (size_ == capability_) {
    InvalidateLRU();
  }

  return EmplaceInternal(desc);
}

ConnectionHandlePtr ConnectionPool::Reuse(const ConnectionDesc& desc) {
  if (!map_.contains(desc)) {
    return InvalidConnHandlePtr();
  }

  return ReuseInternal(desc);

}

ConnectionHandlePtr ConnectionPool::ReuseOrEmplace(const ConnectionDesc& desc) {
  if (!map_.contains(desc)) {
    return EmplaceInternal(desc);
  }

  return Reuse(desc);
}

void ConnectionPool::Invalidate() {
  lru_list_.clear();
  map_.clear();
}

ConnectionHandlePtr ConnectionPool::EmplaceInternal(const ConnectionDesc& desc) {
  if (!map_.contains(desc)) {
    map_.emplace(std::make_pair(desc, std::make_pair(std::vector<List::iterator>{}, 0)));
  }

  auto iter = map_.find(desc);
  auto& array = Array(iter);
  std::size_t npos = 0;
  for (; npos < array.size(); ++npos) {
    if (array[npos] == lru_list_.end()) {
      lru_list_.emplace_front(std::make_shared<ConnectionHandle>(desc, npos));
      array[npos] = lru_list_.begin();
    }
  }

  lru_list_.emplace_front(std::make_shared<ConnectionHandle>(desc, npos));
  array.emplace_back(lru_list_.begin());

  ++RealArraySize(iter);
  ++size_;

  return lru_list_.front();
}

ConnectionHandlePtr ConnectionPool::ReuseInternal(const ConnectionDesc& desc) {
  auto iter = map_.find(desc);
  auto conn_ptr = InvalidConnHandlePtr();

  for (auto& lru_list_iter : Array(iter)) {
    auto& ptr = *lru_list_iter;
    if (!CheckOccupied(ptr)) {
      lru_list_.erase(lru_list_iter);
      lru_list_.push_front(ptr);
      lru_list_iter = lru_list_.begin();
      
      conn_ptr = ptr;
    }
  }

  return conn_ptr;
}

void ConnectionPool::InvalidateLRU() {
  auto iter = lru_list_.rbegin();
  for (; iter != lru_list_.rend(); ++iter) {
    auto& ptr=  *iter;
    if (!CheckOccupied(ptr)) {
      return InvalidateInternal(ptr->locator);
    }
  }

  /* Too many occupied connections */
  throw std::exception();
}


void ConnectionPool::InvalidateInternal(ConnectionHandle::Locator locator) {
  auto iter = map_.find(locator.conn_desc);
  auto& array = Array(iter);
  auto& lru_list_iter = array[locator.npos];

  if (lru_list_iter == lru_list_.end()) {
    return;
  }

  lru_list_.erase(lru_list_iter);
  lru_list_iter = lru_list_.end();
  --RealArraySize(iter);
  --size_;

  if (RealArraySize(iter) == 0) {
    array.clear();
  }
}
}  // namespace protocol
}  // namespace quokkaquery