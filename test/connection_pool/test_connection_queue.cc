#include <gtest/gtest.h>

#include "connection.h"
#include "connection_factory.h"
#include "connection_queue.h"

using namespace quokkaquery::cp;

TEST(TestConnectionQueue, constructor) {
  ConnectionQueue queue;
  EXPECT_TRUE(queue.Empty());
}

TEST(TestConnectionQueue, insert) {
  ConnectionDesc conn_desc{"dbname", "username", "parameter"};
  ConnectionQueue queue;

  auto iter = queue.Insert(std::make_unique<ConnectionQueue::Entry>(
    conn_desc,
    0,
    ConnectionFactory::GetConnection(conn_desc),
    std::future<void>()
  ));

  auto& ptr = *iter;

  std::equal_to<ConnectionDesc> compare;
  EXPECT_TRUE(compare(conn_desc, ptr->conn_desc));
  EXPECT_EQ(ptr->conn_map_idx, 0);
  EXPECT_TRUE(ptr->conn_ptr != nullptr);
}

TEST(TestConnectionQueue, pop) {
  ConnectionDesc conn_desc{"dbname", "username", "parameter"};
  ConnectionQueue queue;
  auto iter = queue.Insert(std::make_unique<ConnectionQueue::Entry>(
    conn_desc,
    0,
    ConnectionFactory::GetConnection(conn_desc),
    std::future<void>()
  ));
  queue.Pop(iter);

  EXPECT_TRUE(queue.Empty());
}