#include <gtest/gtest.h>
#include <boost/asio.hpp>
#include <memory>
#include <future>

#include "connection.h"
#include "server.h"

using namespace quokkaquery::protocol;
using boost::asio::ip::tcp;

namespace {
constexpr int DFLT_PORT_NUMBER = 65432;
}  // namespace anonymous

class TestConnectionToUser : public ::testing::Test {
 protected:
  void SetUp() override {
    io_context = std::make_unique<boost::asio::io_context>();
    server = std::make_unique<Server>(*io_context, ::DFLT_PORT_NUMBER);
    future = std::make_unique<std::future<tcp::socket>>(
      std::async(std::launch::async, [this]() { 
        this->io_context->run(); 
        return this->server->Accept();
    }));
  }

  void TearDown() override {
    server->Close();
  }

  std::unique_ptr<boost::asio::io_context> io_context;
  std::unique_ptr<std::future<tcp::socket>> future;
  std::unique_ptr<Server> server;
};