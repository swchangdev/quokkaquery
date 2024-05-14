#ifndef CONFIG_DASHBOARD_H_
#define CONFIG_DASHBOARD_H_

#include <string>        /* for std::string */
#include <unordered_map> /* for std::unordered_map */

#include "parameter.h"
#include "parameter_desc.h"

namespace config {
class Dashboard final {
 public:
  using TableType = std::unordered_map<ParameterDesc, Parameter>;
  using Iterator = TableType::iterator;
  using ConstIterator = TableType::const_iterator;

  Dashboard();
  ~Dashboard() = default;

  void Populate();
  const bool Empty() const;

  Iterator begin() noexcept;
  ConstIterator begin() const noexcept;
  ConstIterator cbegin() const noexcept;

  Iterator end() noexcept;
  ConstIterator end() const noexcept;
  ConstIterator cend() const noexcept;

  ConstIterator Find(const ParameterDesc& desc) const;
  Iterator Find(const ParameterDesc& desc);

 private:
  std::string raw_data_;
  TableType param_map_;
};
}  // namespace config
#endif /* CONFIG_CATALOG_H_ */
