#ifndef COMMON_EXCEPTION_H_
#define COMMON_EXCEPTION_H_

#include <stdexcept>
#include <string>

enum class ExceptionType {
  CTRL_INVALID_OPTION
};

class Exception : std::exception {
  public:
    explicit Exception(std::exception exception, ExceptionType type)
      : std::exception::exception(exception) {}

    virtual const char *what() const noexcept override {
      std::string header("exception: ");
    }

  private:
    ExceptionType type_;
};

#endif /* COMMON_EXCEPTION_H_ */
