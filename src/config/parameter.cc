#include "parameter.h"

namespace quokkaquery {
namespace config {
ListParameter::ListParameter(const ListParameter::value_type& value,
                             const ListParameter::list_type& valid_list)
 : StringParameter(value), valid_list_(valid_list) {
  if (!ValidateValue(value)) {
    throw std::exception();
  }
}

const bool ListParameter::ValidateValue(const ListParameter::value_type& value) const {
  bool found = false;
  for (auto option : valid_list_) {
    if (option.compare(value) == 0) {
      found = true;
      break;
    }
  }
  return found;
}

RangeParameter::RangeParameter(RangeParameter::value_type value,
                               const RangeParameter::range_type& valid_range)
 : IntegerParameter(value), valid_range_(valid_range) {
  if (!ValidateValue(value)) {
    throw std::exception();
  }
}

const bool RangeParameter::ValidateValue(const RangeParameter::value_type& value) const {
  return value >= valid_range_[0] && value <= valid_range_[1];
}

FlagParameter::FlagParameter(FlagParameter::value_type value)
 : BooleanParameter(value) {}

const bool FlagParameter::ValidateValue(const bool& value) const {
  return true;
}

IPv4Parameter::IPv4Parameter(const IPv4Parameter::value_type& value)
 : StringParameter(value) {
  if (!ValidateValue(value)) {
    throw std::exception();
  }
}

const bool IPv4Parameter::ValidateValue(const value_type& value) const {
  /* TODO how? */
  return true;
}
}  // namespace config
}  // namespace quokkaquery