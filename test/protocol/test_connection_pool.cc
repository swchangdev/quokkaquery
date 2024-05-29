#include <gtest/gtest.h>
#include "connection_pool.h"

using namespace quokkaquery::protocol;

constexpr int DFLT_CONNECTION_POOL_SIZE = 1;
TEST(TestConnectionPool, constructor) {
  ConnectionPool pool(DFLT_CONNECTION_POOL_SIZE);

  EXPECT_TRUE(pool.Empty());
  EXPECT_EQ(pool.Size(), 0);
  EXPECT_EQ(pool.Capability(), DFLT_CONNECTION_POOL_SIZE);
}

TEST(TestConnectionPool, emplace) {
  ConnectionPool pool(DFLT_CONNECTION_POOL_SIZE);
  ConnectionDesc conn_desc{"dbname", "username", "parameter"};

  auto conn_handle = pool.Emplace(conn_desc);

  EXPECT_FALSE(pool.Empty());
  EXPECT_EQ(pool.Size(), 1);
  EXPECT_EQ(pool.Capability(), 1);

  std::equal_to<ConnectionDesc> compare;
  EXPECT_TRUE(compare(conn_desc, conn_handle->locator.conn_desc));
  EXPECT_EQ(conn_handle->locator.npos, 0);
}

TEST(TestConnectionPool, too_many_emplace) {
  ConnectionPool pool(DFLT_CONNECTION_POOL_SIZE);
  ConnectionDesc conn_desc1{"dbname", "username", "parameter1"};
  ConnectionDesc conn_desc2{"dbname", "username", "parameter2"};

  pool.Emplace(conn_desc1);
  pool.Emplace(conn_desc2);  // conn_desc1 is invalidated

  auto conn1 = pool.Reuse(conn_desc1);
  auto conn2 = pool.Reuse(conn_desc2);

  EXPECT_FALSE(conn1);
  EXPECT_TRUE(conn2);
  EXPECT_EQ(pool.Size(), 1);
}

TEST(TestConnectionPool, reuse) {
  ConnectionPool pool(DFLT_CONNECTION_POOL_SIZE);
  ConnectionDesc conn_desc{"dbname", "username", "parameter"};

  auto emplaced = pool.Emplace(conn_desc);
  auto reused = pool.Reuse(conn_desc);

  EXPECT_EQ(emplaced.get(), reused.get());
  
  std::equal_to<ConnectionDesc> compare;
  EXPECT_TRUE(compare(emplaced->locator.conn_desc, reused->locator.conn_desc));
  EXPECT_EQ(emplaced->locator.npos, reused->locator.npos);
}

TEST(TestConnectionPool, reuse_invalid) {
  ConnectionPool pool(DFLT_CONNECTION_POOL_SIZE);
  ConnectionDesc right_conn_desc{"dbname", "username", "parameter1"};
  ConnectionDesc wrong_conn_desc{"dbname", "username", "parameter2"};

  pool.Emplace(right_conn_desc);

  auto reused = pool.Reuse(wrong_conn_desc);
  EXPECT_EQ(reused, nullptr);
}

TEST(TestConnectionPool, resize) {
  ConnectionPool pool(DFLT_CONNECTION_POOL_SIZE);
  ConnectionDesc conn_desc{"dbname", "username", "parameter"};
  
  pool.Emplace(conn_desc);
  pool.Resize(2*DFLT_CONNECTION_POOL_SIZE);

  auto conn_ptr = pool.Emplace(conn_desc);

  EXPECT_EQ(conn_ptr->locator.npos, 1);
  EXPECT_EQ(pool.Size(), 2);
}

TEST(TestConnectionPool, invalidate_all) {
  ConnectionPool pool(4 * DFLT_CONNECTION_POOL_SIZE);

  pool.Emplace(ConnectionDesc{"dbname", "username", "parameter1"});
  pool.Emplace(ConnectionDesc{"dbname", "username", "parameter2"});
  pool.Emplace(ConnectionDesc{"dbname", "username", "parameter3"});
  pool.Emplace(ConnectionDesc{"dbname", "username", "parameter4"});

  pool.Invalidate();

  EXPECT_TRUE(pool.Empty());
}