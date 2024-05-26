#include "connection_queue.h"

#include "connection.h"

namespace quokkaquery {
namespace cp {
const bool ConnectionQueue::Empty() const {
  return list_.empty();
}

const std::size_t ConnectionQueue::Size() const {
  return list_.size();
}

ConnectionQueue::Iterator ConnectionQueue::Insert(std::unique_ptr<ConnectionQueue::Entry> obj) {
  list_.emplace_back(std::move(obj));
  return --list_.end();
}

void ConnectionQueue::Pop(ConnectionQueue::ConstIterator iter) {
  list_.erase(iter);
}

ConnectionQueue::Iterator ConnectionQueue::begin() {
  return list_.begin();
}

ConnectionQueue::ConstIterator ConnectionQueue::begin() const {
  return list_.cbegin();
}

ConnectionQueue::ConstIterator ConnectionQueue::cbegin() const {
  return list_.cbegin();
}

ConnectionQueue::Iterator ConnectionQueue::end() {
  return list_.end();
}

ConnectionQueue::ConstIterator ConnectionQueue::end() const {
  return list_.cend();
}

ConnectionQueue::ConstIterator ConnectionQueue::cend() const {
  return list_.cend();
}
}  // namespace cp
}  // namespace quokkaquery