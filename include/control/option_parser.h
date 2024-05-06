#ifndef CONTROL_OPTION_PARSER_H_
#define CONTROL_OPTION_PARSER_H_

#include <string>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace ctrl {
class OptionParser {
  public:
    OptionParser(int argc, char **argv);
    OptionParser(int argc, const char **argv);
    ~OptionParser() = default;

    template <typename T>
    const T GetOptionValue(std::string &&key) const {
      return variables_map_[std::forward<std::string>(key)].as<T>();
    }

    const bool ContainsOption(std::string &&key) const;
    const po::options_description& GetAllowedOptions() const;

  private:
    po::options_description allowed_options_;
    po::variables_map variables_map_;
};
}  // namespace ctrl

#endif /* CONTROL_OPTION_PARSER_H_ */