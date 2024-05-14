#include <gtest/gtest.h>

#include "connection.h"
#include "connection_factory.h"
#include "pool.h"

TEST(TestConnectionPool, constructor) {
  conn::Pool pool;
  EXPECT_TRUE(pool.Empty());
}

TEST(TestConnectionPool, insert) {
  conn::ConnectionDesc conn_desc {
    "dbname",
    "username",
    ""
  };

  conn::Pool pool;
  auto iter = pool.Insert(std::make_unique<conn::Pool::Entry>(
    conn_desc,
    0,
    conn::ConnectionFactory::GetConnection(conn_desc),
    std::future<void>()
  ));

  auto& ptr = *iter;
  EXPECT_EQ(ptr->conn_desc, conn_desc);
  EXPECT_EQ(ptr->conn_map_idx, 0);
  EXPECT_TRUE(ptr->conn_ptr != nullptr);
}

TEST(TestConnectionPool, pop) {
  conn::ConnectionDesc conn_desc {
    "dbname",
    "username",
    ""
  };

  conn::Pool pool;
  auto iter = pool.Insert(std::make_unique<conn::Pool::Entry>(
    conn_desc,
    0,
    conn::ConnectionFactory::GetConnection(conn_desc),
    std::future<void>()
  ));
  pool.Pop(iter);

  EXPECT_TRUE(pool.Empty());
}