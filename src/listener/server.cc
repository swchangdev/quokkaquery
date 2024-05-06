#include "server.h"
#include "config.h"
#include <boost/asio.hpp>

namespace asio = boost::asio;
namespace ip = boost::asio::ip;

using io_context = asio::io_context;
using tcp = boost::asio::ip::tcp;

namespace lsnr {
Server::Server(const common::Config &config)
 : config_(config) {
  // TODO: setup shared memory area for connection pool

}

void Server::operator()() {
  int port_number = config_["listener"]["lsnr_port"].value_or(65432);
  try {
    while (true) {
      io_context io_context;
      tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port_number)); 
      tcp::socket socket(io_context);

      acceptor.accept(socket);

      // TODO: decode the message and get connection string
      auto conn_str = GetConnStringFromMessage(socket);

      // TODO: check if conn_str is in the connection pool
      if (connection_pool.Count(conn_str)) {
        auto connection = connection_pool.Get(conn_str);
      } else {
        // create DB connection and cache it in the connection pool
        // may need to think about the cache eviction process here
      }

      // use std::async to start a new worker thread
    }
  }
}
}  // namespace lsnr