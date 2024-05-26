#include <gtest/gtest.h>

#include <memory>
#include <thread>
#include <vector>

#include "database_connection.h"
#include "mock_server.h"

using namespace quokkaquery::cp;

namespace {
constexpr int DFLT_PORT_NUMBER = 65432;
static inline std::vector<char> Encode(const std::string& message) {
  return std::vector<char>(message.begin(), message.end());
}
}  // namespace anonymous

class TestConnectionDBClient : public ::testing::Test {
 protected:
  void SetUp() override {
    server = std::make_shared<test::MockServer>(::DFLT_PORT_NUMBER);
    future = std::make_unique<std::future<void>>(
        std::async(std::launch::async, [this]() { this->server->Run(); }));
  }

  void TearDown() override {
    server->Stop();
    future->get();
  }

  std::unique_ptr<std::future<void>> future;
  std::shared_ptr<test::MockServer> server;
};

TEST_F(TestConnectionDBClient, connect) {
  DatabaseDesc desc{"localhost", std::to_string(::DFLT_PORT_NUMBER)};
  EXPECT_NO_THROW(
    DatabaseConnection db_client(desc);
  );
}

TEST_F(TestConnectionDBClient, read_and_write) {
  DatabaseDesc desc{"localhost", std::to_string(::DFLT_PORT_NUMBER)};
  DatabaseConnection db_client(desc);
  
  auto message = ::Encode("Hello World!");
  db_client.Write(message);

  auto reply_length = db_client.Read(message.size());
  auto& buffer = db_client.GetReadBuffer();
  auto reply = std::vector<char>(buffer.begin(), buffer.begin() + reply_length);

  EXPECT_EQ(message, reply);
}