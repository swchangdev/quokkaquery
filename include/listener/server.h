#ifndef LISTENER_SERVER_H_
#define LISTENER_SERVER_H_

#include <vector>

#include "task.h"

namespace common {
class Config;
}  // namespace common

namespace lsnr {
class Server final {
  public:
    explicit Server(const common::Config &);
    Server(const Server &) = delete;
    Server(Server &&) = delete;
    ~Server() = default;

    void operator()();
  
  private:
    const common::Config &config_;
    std::vector<> 
};
}  // namespace lsnr

#endif /* LISTENER_SERVER_H_ */