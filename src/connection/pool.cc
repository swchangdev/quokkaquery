#include "pool.h"

#include "connection.h"

namespace conn {
const bool Pool::Empty() const {
  return list_.empty();
}

const std::size_t Pool::Size() const {
  return list_.size();
}

Pool::Iterator Pool::Insert(std::unique_ptr<Pool::Entry> obj) {
  list_.emplace_back(std::move(obj));
  return --list_.end();
}

void Pool::Pop(Pool::ConstIterator iter) {
  list_.erase(iter);
}

Pool::Iterator Pool::begin() {
  return list_.begin();
}

Pool::ConstIterator Pool::begin() const {
  return list_.cbegin();
}

Pool::ConstIterator Pool::cbegin() const {
  return list_.cbegin();
}

Pool::Iterator Pool::end() {
  return list_.end();
}

Pool::ConstIterator Pool::end() const {
  return list_.cend();
}

Pool::ConstIterator Pool::cend() const {
  return list_.cend();
}
}  // namespace conn