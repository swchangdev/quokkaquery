#ifndef CONTROL_VERSION_H_
#define CONTROL_VERISON_H_

#include <string_view>

namespace ctrl {
constexpr std::string_view GetCurrentVersion() {
  /* CURRENT_VERSION MACRO is defined in CMakeLists.txt as a compiler definition*/
  return CURRENT_VERSION; 
}
}  // namespace ctrl

#endif /* CONTROL_VERESION_H_ */