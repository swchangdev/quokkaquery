#include "database_connection.h"

namespace quokkaquery {
namespace cp {
using boost::asio::ip::tcp;
constexpr int READ_BUFFER_MAX_SIZE = 1024;

DatabaseConnection::DatabaseConnection(const DatabaseDesc& desc)
 : io_context_(),
   socket_(io_context_),
   read_buffer_(READ_BUFFER_MAX_SIZE) {
  tcp::resolver resolver(io_context_);
  auto endpoints = resolver.resolve(desc.ip_addr, desc.port);
  boost::asio::connect(socket_, endpoints);
}

DatabaseConnection::~DatabaseConnection() {
  if (socket_.is_open()) {
    socket_.close();
  }
  io_context_.stop();
}

const std::size_t DatabaseConnection::Write(const DatabaseConnection::BufferType& message) {
  /* boost::asio::write will automatically write all supplied buffers */
  return boost::asio::write(socket_, boost::asio::buffer(message));
}

const std::size_t DatabaseConnection::Read(const std::size_t size) {
  /* blocking */
  socket_.wait(tcp::socket::wait_read);
  return boost::asio::read(socket_, boost::asio::buffer(read_buffer_, size));
}

const DatabaseConnection::BufferType& DatabaseConnection::GetReadBuffer() const {
  return read_buffer_;
}
}  // namespace cp
}  // namespace quokkaquery