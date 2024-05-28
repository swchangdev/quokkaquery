#ifndef QQ_PROTOCOL_CONNECTION_H_
#define QQ_PROTOCOL_CONNECTION_H_

#include <boost/asio.hpp>
#include <vector>
#include <string>
#include <memory>

namespace quokkaquery {
namespace protocol {
namespace impl {
using tcp = boost::asio::ip::tcp;
using endpoints = boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp>;
class ConnectionInterface {
 public:
  using BufferType = std::vector<char>;

  ConnectionInterface(impl::tcp::socket&&);
  virtual ~ConnectionInterface() = 0;

  const std::size_t Write(const BufferType& message);
  const std::size_t Read(const std::size_t read_length);
  const BufferType& GetReadBuffer() const;

 protected:
  impl::tcp::socket socket_;
  BufferType read_buffer_;
};
}  // namespace impl

class UserConnection : public impl::ConnectionInterface {
 public:
  using Pointer = std::shared_ptr<UserConnection>;
  virtual ~UserConnection() = default;
  static Pointer Create(impl::tcp::socket&& socket) {
    return Pointer(new UserConnection(std::move(socket)));
  }

 private:
  UserConnection(impl::tcp::socket&&);
};

class DatabaseConnection : public impl::ConnectionInterface {
 public:
  using Pointer = std::shared_ptr<DatabaseConnection>;
  virtual ~DatabaseConnection() = default;
  static Pointer Create(impl::tcp::socket&& socket, const impl::endpoints& ep) {
    return Pointer(new DatabaseConnection(std::move(socket), ep));
  }

 private:
  DatabaseConnection(impl::tcp::socket&&, const impl::endpoints&);
};
}  // namespace protocol
}  // namespace quokkaquery

#endif /* QQ_PROTOCOL_CONNECTION_H_ */