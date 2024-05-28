#include "connection.h"

namespace quokkaquery {
namespace protocol {
namespace impl {
constexpr std::size_t READ_BUFFER_MAX_SIZE = 1024;

ConnectionInterface::ConnectionInterface(impl::tcp::socket&& socket)
    : socket_(std::move(socket)),
      read_buffer_(READ_BUFFER_MAX_SIZE) {}

ConnectionInterface::~ConnectionInterface() {
  if (socket_.is_open()) {
    socket_.close();
  }
}

const std::size_t ConnectionInterface::Write(const ConnectionInterface::BufferType& message) {
  return boost::asio::write(socket_, boost::asio::buffer(message));
}

const std::size_t ConnectionInterface::Read(const std::size_t read_length) {
  socket_.wait(impl::tcp::socket::wait_read);
  return boost::asio::read(socket_, boost::asio::buffer(read_buffer_, read_length));
}

const ConnectionInterface::BufferType& ConnectionInterface::GetReadBuffer() const {
  return read_buffer_;
}
}  // namespace impl

UserConnection::UserConnection(impl::tcp::socket&& socket)
    : ConnectionInterface(std::move(socket)) {}

DatabaseConnection::DatabaseConnection(impl::tcp::socket&& socket, const impl::endpoints& ep)
    : ConnectionInterface(std::move(socket)) {
  boost::asio::connect(socket_, ep);
}
}  // namespace protocol
}  // namespace quokkaquery