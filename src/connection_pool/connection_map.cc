#include "connection_map.h"

#include "connection_desc.h"
#include "connection_factory.h"

namespace quokkaquery {
namespace cp {
static inline const bool CheckOccupied(std::shared_ptr<Connection> ptr) {
  /* Unoccupied only if it's referenced by map and pool */
  return !ptr && (ptr.use_count() > 2);
}

ConnectionMap::ConnectionMap(std::size_t pool_size)
 : conn_table_(pool_size), 
   size_(0),
   capability_(pool_size) {}

const bool ConnectionMap::Empty() const {
  return size_ == 0;
}

const std::size_t ConnectionMap::Size() const {
  return size_;
}

const std::size_t ConnectionMap::Capability() const {
  return capability_;
}

void ConnectionMap::Resize(std::size_t new_size) {
  conn_table_.rehash(new_size);
  capability_ = new_size;
}

const std::size_t ConnectionMap::Insert(const ConnectionDesc& desc, std::shared_ptr<Connection> conn_ptr) {
  auto iter = conn_table_.find(desc);

  std::size_t conn_index = 0;
  if (iter == conn_table_.end()) {
    conn_table_[desc].emplace_back(conn_ptr);
  } else {
    auto& array = iter->second;
    for (; conn_index < array.size(); ++conn_index) {
      auto &ptr = array[conn_index];
      if (!ptr) {
        ptr = conn_ptr;
        break;
      }
    }

    if (conn_index == array.size()) {
      array.emplace_back(conn_ptr);
    }
  }

  ++size_;

  return conn_index;
}

void ConnectionMap::Delete(const ConnectionDesc& desc, std::size_t index) {
  auto iter = conn_table_.find(desc);
  auto& conn = iter->second[index];

  conn.reset();
  --size_;
}

std::shared_ptr<Connection> ConnectionMap::Get(const ConnectionDesc& desc, std::size_t index) {
  auto iter = conn_table_.find(desc);

  if (iter == conn_table_.end()) {
    return ConnectionFactory::GetInvalidConnection();
  }

  auto &array = iter->second;
  if (array.size() <= index) {
    return ConnectionFactory::GetInvalidConnection();
  }

  return array[index];
}

std::shared_ptr<Connection> ConnectionMap::Reuse(const ConnectionDesc& desc) {
  auto iter = conn_table_.find(desc);
  if (iter == conn_table_.end()) {
    return ConnectionFactory::GetInvalidConnection();
  }

  auto conn_ptr = ConnectionFactory::GetInvalidConnection();
  for (auto& conn : iter->second) {
    /* check conn if it is unoccupied and not a nullptr */
    if (!CheckOccupied(conn)) {
      conn_ptr = conn;
    }
  }

  return conn_ptr;
}
}  // namespace cp
}  // namespace quokkaquery