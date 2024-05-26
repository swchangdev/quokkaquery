#ifndef QQ_CP_DATABASE_CONNECTION_H_
#define QQ_CP_DATABASE_CONNECTION_H_

#include <boost/asio.hpp>
#include <vector>
#include <string>

using boost::asio::ip::tcp;

namespace quokkaquery {
namespace cp {
struct DatabaseDesc {
  const std::string ip_addr;
  const std::string port;
};

class DatabaseConnection {
 public:
  DatabaseConnection(const DatabaseDesc& desc)
   : io_context_(),
     socket_(io_context_),
     read_buffer_(READ_BUFFER_MAX_SIZE) {
    tcp::resolver resolver(io_context_);
    auto endpoints = resolver.resolve(desc.ip_addr, desc.port);
    boost::asio::connect(socket_, endpoints);
  }
  ~DatabaseConnection() = default;

  void Write(const std::string &message) {
    boost::asio::write(socket_, boost::asio::buffer(message));
  }

  const std::size_t Read(const std::size_t size) {
    socket_.wait(tcp::socket::wait_read);
    return boost::asio::read(socket_, boost::asio::buffer(read_buffer_, size));
  }

  const std::vector<char>& GetReadBuffer() const {
    return read_buffer_;
  }

 private:
  const int READ_BUFFER_MAX_SIZE = 1024;
  boost::asio::io_context io_context_;
  tcp::socket socket_;
  std::vector<char> read_buffer_;
};
}  // namespace cp
}  // namespace quokkaquery

#endif /* QQ_CP_DATABASE_CONNECTION_H_ */