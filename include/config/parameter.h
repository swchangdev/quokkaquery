#ifndef CONFIG_PARAMETER_H_
#define CONFIG_PARAMETER_H_

#include <memory>  /* for std::unique_ptr */
#include <string>  /* for std::string */
#include <variant> /* for std::variant */
#include <vector>  /* for std::vector */

namespace config {
template <typename T>
class ParameterBase {
 public:
  explicit ParameterBase(T value) : value_(value) {}
  virtual ~ParameterBase() {}

  void Set(const T& value) {
    if (ValidateValue(value)) {
      value_ = value;
    }
  }

  const T Get() const { return value_; }

 protected:
  virtual const bool ValidateValue(const T& value) const = 0;

 private:
  T value_;
};

using StringParameter = ParameterBase<std::string>;
using IntegerParameter = ParameterBase<int>;
using BooleanParameter = ParameterBase<bool>;

class ListParameter : public StringParameter {
 public:
  using value_type = std::string;
  using list_type = std::vector<std::string>;

  ListParameter(const value_type&, const list_type&);
  ~ListParameter() noexcept = default;

 protected:
  const bool ValidateValue(const value_type& value) const override;

 private:
  list_type valid_list_;
};

class RangeParameter : public IntegerParameter {
 public:
  using value_type = int;
  using range_type = std::vector<int>;

  RangeParameter(value_type value, const range_type& valid_range);
  ~RangeParameter() noexcept = default;

 protected:
  const bool ValidateValue(const value_type& value) const override;
 
 private:
  range_type valid_range_;
};

class FlagParameter : public BooleanParameter {
 public:
  using value_type = bool;

  explicit FlagParameter(value_type value);
  ~FlagParameter() noexcept = default;

 protected:
  const bool ValidateValue(const bool& value) const override;
};

class IPv4Parameter : public StringParameter {
 public:
  using value_type = std::string;

  IPv4Parameter(const value_type& value);
  ~IPv4Parameter() noexcept = default;

 protected:
  const bool ValidateValue(const value_type& value) const override;
};

struct Parameter {
  enum class TypeId : int {
    LIST = 0,
    RANGE,
    FLAG,
    IPV4,
  };

  using Value = std::variant<
    ListParameter,
    RangeParameter,
    FlagParameter,
    IPv4Parameter
  >;

  TypeId type;
  std::unique_ptr<Value> value;
};

}  // namespace config

#endif /* CONFIG_PARAMETER_H_ */