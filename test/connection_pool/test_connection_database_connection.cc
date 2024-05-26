#include <gtest/gtest.h>
#include <vector>
#include <chrono>
#include <thread>
#include <memory>

#include "database_connection.h"
#include "mock_server.h"

constexpr int DFLT_PORT_NUMBER = 65432;

using namespace quokkaquery::cp;

class TestConnectionDBClient : public ::testing::Test {
 protected:
  void SetUp() override {
    server = std::make_shared<test::MockServer>(DFLT_PORT_NUMBER);
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
  DatabaseDesc desc{"localhost", std::to_string(DFLT_PORT_NUMBER)};
  EXPECT_NO_THROW(
    DatabaseConnection db_client(desc);
  );
}

TEST_F(TestConnectionDBClient, read_and_write) {
  DatabaseDesc desc{"localhost", std::to_string(DFLT_PORT_NUMBER)};
  DatabaseConnection db_client(desc);
  
  auto message = std::string("Hello World!");
  db_client.Write(message);

  auto reply_length = db_client.Read(message.size());
  auto& buffer = db_client.GetReadBuffer();
  auto reply = std::string(buffer.begin(), buffer.begin() + reply_length);

  EXPECT_EQ(message.compare(reply), 0);
}