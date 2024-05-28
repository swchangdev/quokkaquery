#include <gtest/gtest.h>

#include <memory>
#include <thread>
#include <vector>

#include "connection.h"
#include "mock_server.h"

using namespace quokkaquery::protocol;

namespace {
constexpr int DFLT_PORT_NUMBER = 65432;
static inline std::vector<char> Encode(const std::string& message) {
  return std::vector<char>(message.begin(), message.end());
}
}  // namespace anonymous

class TestConnectionToDB : public ::testing::Test {
 protected:
  void SetUp() override {
    io_context = std::make_unique<boost::asio::io_context>();
    server = std::make_unique<test::MockServer>(*io_context, ::DFLT_PORT_NUMBER);
    future = std::make_unique<std::future<void>>(
        std::async(std::launch::async, [this]() { this->io_context->run(); }));
  }

  void TearDown() override {
    server->Stop();
    future->get();
  }

  std::unique_ptr<boost::asio::io_context> io_context;
  std::unique_ptr<std::future<void>> future;
  std::unique_ptr<test::MockServer> server;
};

TEST_F(TestConnectionToDB, connect) {
  auto& io_ctx = *io_context;

  tcp::resolver resolver(io_ctx);
  auto endpoints = resolver.resolve("localhost", std::to_string(::DFLT_PORT_NUMBER));

  EXPECT_NO_THROW(
    auto db_conn = DatabaseConnection::Create(tcp::socket(io_ctx), endpoints);
  );
}

TEST_F(TestConnectionToDB, read_and_write) {
  auto& io_ctx = *io_context;

  tcp::resolver resolver(io_ctx);
  auto endpoints = resolver.resolve("localhost", std::to_string(::DFLT_PORT_NUMBER));

  auto db_conn = DatabaseConnection::Create(tcp::socket(io_ctx), endpoints);

  auto write_length = db_conn->Write(::Encode("Hello World!"));
  auto reply_length = db_conn->Read(write_length);
  EXPECT_EQ(write_length, reply_length);

  auto& buffer = db_conn->GetReadBuffer();
  auto reply = std::vector<char>(buffer.begin(), buffer.begin() + reply_length);

  EXPECT_EQ(reply, ::Encode("Hello World!"));
}