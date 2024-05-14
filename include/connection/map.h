#ifndef QQ_CONNECTION_MAP_H_
#define QQ_CONNECTION_MAP_H_

#include <memory>        /* for std::shared_ptr */
#include <unordered_map> /* for std::unordered_map */
#include <vector>        /* for std::vector */

#include "connection_desc.h"

namespace conn {
class Connection;

class Map {
 public:
  using ValueType = std::vector<std::shared_ptr<Connection>>;
  using TableType = std::unordered_map<ConnectionDesc, ValueType>;

  explicit Map(std::size_t pool_size);
  ~Map() = default;

  const bool Empty() const;
  const std::size_t Size() const;
  const std::size_t Capability() const;

  void Resize(std::size_t new_size);

  const std::size_t Insert(const ConnectionDesc&);
  void Delete(const ConnectionDesc&, std::size_t index);

  std::shared_ptr<Connection> Get(const ConnectionDesc&, std::size_t index);
  std::shared_ptr<Connection> Reuse(const ConnectionDesc&);

 private:
  TableType conn_table_;
  std::size_t size_;
  std::size_t capability_;
};

}  // namespace conn
#endif /* QQ_CONNECTION_MAP_H_ */