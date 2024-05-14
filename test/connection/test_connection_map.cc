#include <gtest/gtest.h>
#include "map.h"
#include "connection_factory.h"

TEST(TestConnectionMap, constructor) {
  conn::Map map(100);

  EXPECT_TRUE(map.Empty());
  EXPECT_EQ(map.Capability(), 100);
}

TEST(TestConnectionMap, insert) {
  conn::Map map(100);
  conn::ConnectionDesc conn_desc("dbname", "username", "parameter");
  auto idx = map.Insert(conn_desc, conn::ConnectionFactory::GetConnection(conn_desc));

  EXPECT_FALSE(map.Empty());
  EXPECT_EQ(map.Size(), 1);
  EXPECT_EQ(idx, 0);
}

TEST(TestConnectionMap, insert_many) {
  conn::Map map(100);
  conn::ConnectionDesc conn_desc("dbname", "username", "parameter");

  map.Insert(conn_desc, conn::ConnectionFactory::GetConnection(conn_desc));
  map.Insert(conn_desc, conn::ConnectionFactory::GetConnection(conn_desc));
  auto idx = map.Insert(conn_desc, conn::ConnectionFactory::GetConnection(conn_desc));

  EXPECT_EQ(map.Size(), 3);
  EXPECT_EQ(idx, 2);
}

TEST(TestConnectionMap, resize) {
  conn::Map map(5);
  conn::ConnectionDesc conn_desc("dbname", "username", "parameter");

  map.Insert(conn_desc, conn::ConnectionFactory::GetConnection(conn_desc));
  map.Insert(conn_desc, conn::ConnectionFactory::GetConnection(conn_desc));
  map.Insert(conn_desc, conn::ConnectionFactory::GetConnection(conn_desc));
  map.Insert(conn_desc, conn::ConnectionFactory::GetConnection(conn_desc));
  auto index = map.Insert(conn_desc, conn::ConnectionFactory::GetConnection(conn_desc));

  auto old_ptr = map.Get(conn_desc, index);

  map.Resize(10);

  auto new_ptr = map.Get(conn_desc, index);
  EXPECT_EQ(old_ptr.get(), new_ptr.get());
  EXPECT_EQ(map.Size(), 5);
  EXPECT_EQ(map.Capability(), 10);
}

TEST(TestConnectionMap, delete_conn) {
  conn::Map map(100);
  conn::ConnectionDesc conn_desc("dbname", "username", "parameter");

  map.Insert(conn_desc, conn::ConnectionFactory::GetConnection(conn_desc));
  auto idx = map.Insert(conn_desc, conn::ConnectionFactory::GetConnection(conn_desc));
  map.Insert(conn_desc, conn::ConnectionFactory::GetConnection(conn_desc));

  map.Delete(conn_desc, idx);

  auto ptr = map.Get(conn_desc, idx);

  EXPECT_EQ(map.Size(), 2);
  EXPECT_EQ(ptr.get(), nullptr);
}

TEST(TestConnectionMap, reuse) {
  conn::Map map(100);
  conn::ConnectionDesc conn_desc("dbname", "username", "parameter");

  auto idx1 = map.Insert(conn_desc, conn::ConnectionFactory::GetConnection(conn_desc));
  auto idx2 = map.Insert(conn_desc, conn::ConnectionFactory::GetConnection(conn_desc));
  map.Delete(conn_desc, idx1);

  auto ptr = map.Get(conn_desc, idx2);
  auto reuse_ptr = map.Reuse(conn_desc);

  EXPECT_EQ(ptr.get(), reuse_ptr.get());
}