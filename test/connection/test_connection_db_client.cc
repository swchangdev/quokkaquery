#include <gtest/gtest.h>
#include <vector>
#include <chrono>
#include <thread>
#include <memory>

#include "database_client.h"
#include "mock_server.h"

using namespace std::chrono_literals;
void Sleep(const std::chrono::nanoseconds ns) {
  std::this_thread::sleep_for(ns);
}

constexpr int DFLT_PORT_NUMBER = 65432;

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
  conn::DatabaseDesc desc{"localhost", std::to_string(DFLT_PORT_NUMBER)};
  EXPECT_NO_THROW(
    conn::DatabaseClient db_client(desc);
  );
}

TEST_F(TestConnectionDBClient, read_and_write) {
  conn::DatabaseDesc desc{"localhost", std::to_string(DFLT_PORT_NUMBER)};
  conn::DatabaseClient db_client(desc);
  
  auto message = std::string("Hello World!");
  db_client.Write(message);

  auto reply_length = db_client.Read(message.size());
  auto& buffer = db_client.GetReadBuffer();
  auto reply = std::string(buffer.begin(), buffer.begin() + reply_length);

  EXPECT_EQ(message.compare(reply), 0);
}