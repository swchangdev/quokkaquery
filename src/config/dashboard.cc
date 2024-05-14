#include "dashboard.h"

#include <memory>

#include "nlohmann/json.hpp"

namespace config {
static inline decltype(auto) CreateListParameter(const nlohmann::json &param_json) {
  const auto valid_list = param_json["type"]["list"].template get<std::vector<std::string>>();
  const auto default_value = param_json["default"].template get<std::string>();
  return ListParameter(default_value, valid_list);
}

static inline decltype(auto) CreateRangeParameter(const nlohmann::json &param_json) {
  const auto valid_range = param_json["type"]["range"].template get<std::vector<int>>();
  const auto default_value = param_json["default"].template get<int>();
  return RangeParameter(default_value, valid_range);
}

static inline decltype(auto) CreateFlagParameter(const nlohmann::json &param_json) {
  const auto default_value = param_json["default"].template get<bool>();
  return FlagParameter(default_value);
}

static inline decltype(auto) CreateIPv4Parameter(const nlohmann::json &param_json) {
  const auto default_value = param_json["default"].template get<std::string>();
  return IPv4Parameter(default_value);
}

static inline Parameter CreateParameter(int type_id, const nlohmann::json& param_json) {
  auto type = static_cast<Parameter::TypeId>(type_id);
  std::unique_ptr<Parameter::Value> value;

  switch(type) {
    case Parameter::TypeId::LIST:
      value = std::make_unique<Parameter::Value>(CreateListParameter(param_json));
      break;
    case Parameter::TypeId::RANGE:
      value = std::make_unique<Parameter::Value>(CreateRangeParameter(param_json));
      break;
    case Parameter::TypeId::FLAG:
      value = std::make_unique<Parameter::Value>(CreateFlagParameter(param_json));
      break;
    case Parameter::TypeId::IPV4:
      value = std::make_unique<Parameter::Value>(CreateIPv4Parameter(param_json));
      break;
    default:
      /* TODO assert? */
      throw std::exception();
  }

  return Parameter{type, std::move(value)};
}

void Dashboard::Populate() {
  auto json = nlohmann::json::parse(raw_data_);
  
  for (const auto& [category, parameters]: json.items()) {
    for (const auto& [index, parameter]: parameters.items()) {
      auto name = parameter["name"].template get<std::string>();
      auto type_id = parameter["type"]["id"].template get<int>();
      ParameterDesc desc{category, name};

      param_map_.emplace(std::make_pair(desc, std::move(CreateParameter(type_id, parameter))));
   }
  }
}

const bool Dashboard::Empty() const {
  return param_map_.empty();
}

Dashboard::Iterator Dashboard::begin() noexcept {
  return param_map_.begin();
}

Dashboard::ConstIterator Dashboard::begin() const noexcept {
  return param_map_.begin();
}

Dashboard::ConstIterator Dashboard::cbegin() const noexcept {
  return param_map_.cbegin();
}

Dashboard::Iterator Dashboard::end() noexcept {
  return param_map_.end();
}

Dashboard::ConstIterator Dashboard::end() const noexcept {
  return param_map_.end();
}

Dashboard::ConstIterator Dashboard::cend() const noexcept {
  return param_map_.cend();
}

Dashboard::ConstIterator Dashboard::Find(const ParameterDesc& desc) const {
  return param_map_.find(desc);
}

Dashboard::Iterator Dashboard::Find(const ParameterDesc& desc) {
  return param_map_.find(desc);
}
}  // namespace config