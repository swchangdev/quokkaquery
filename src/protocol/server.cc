#include "server.h"

using boost::asio::ip::tcp;

namespace quokkaquery {
namespace protocol {
Server::Server(boost::asio::io_context& io_context, const int port_number)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port_number)) {
  /* set SO_REUSEADDR */
  boost::asio::socket_base::reuse_address option(true);
  acceptor_.set_option(option);
}

tcp::socket Server::Accept() {
  return acceptor_.accept();
}

void Server::Close() {
  acceptor_.close();
}
}  // namespace protocol
}  // namespace quokkaquery