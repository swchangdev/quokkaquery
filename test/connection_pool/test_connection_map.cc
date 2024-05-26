#include <gtest/gtest.h>
#include "connection_map.h"
#include "connection_factory.h"

using namespace quokkaquery::cp;

TEST(TestConnectionMap, constructor) {
  ConnectionMap map(100);

  EXPECT_TRUE(map.Empty());
  EXPECT_EQ(map.Capability(), 100);
}

TEST(TestConnectionMap, insert) {
  ConnectionMap map(100);
  ConnectionDesc conn_desc("dbname", "username", "parameter");
  auto idx = map.Insert(conn_desc, ConnectionFactory::GetConnection(conn_desc));

  EXPECT_FALSE(map.Empty());
  EXPECT_EQ(map.Size(), 1);
  EXPECT_EQ(idx, 0);
}

TEST(TestConnectionMap, insert_many) {
  ConnectionMap map(100);
  ConnectionDesc conn_desc("dbname", "username", "parameter");

  map.Insert(conn_desc, ConnectionFactory::GetConnection(conn_desc));
  map.Insert(conn_desc, ConnectionFactory::GetConnection(conn_desc));
  auto idx = map.Insert(conn_desc, ConnectionFactory::GetConnection(conn_desc));

  EXPECT_EQ(map.Size(), 3);
  EXPECT_EQ(idx, 2);
}

TEST(TestConnectionMap, resize) {
  ConnectionMap map(5);
  ConnectionDesc conn_desc("dbname", "username", "parameter");

  map.Insert(conn_desc, ConnectionFactory::GetConnection(conn_desc));
  map.Insert(conn_desc, ConnectionFactory::GetConnection(conn_desc));
  map.Insert(conn_desc, ConnectionFactory::GetConnection(conn_desc));
  map.Insert(conn_desc, ConnectionFactory::GetConnection(conn_desc));
  auto index = map.Insert(conn_desc, ConnectionFactory::GetConnection(conn_desc));

  auto old_ptr = map.Get(conn_desc, index);

  map.Resize(10);

  auto new_ptr = map.Get(conn_desc, index);
  EXPECT_EQ(old_ptr.get(), new_ptr.get());
  EXPECT_EQ(map.Size(), 5);
  EXPECT_EQ(map.Capability(), 10);
}

TEST(TestConnectionMap, delete_conn) {
  ConnectionMap map(100);
  ConnectionDesc conn_desc("dbname", "username", "parameter");

  map.Insert(conn_desc, ConnectionFactory::GetConnection(conn_desc));
  auto idx = map.Insert(conn_desc, ConnectionFactory::GetConnection(conn_desc));
  map.Insert(conn_desc, ConnectionFactory::GetConnection(conn_desc));

  map.Delete(conn_desc, idx);

  auto ptr = map.Get(conn_desc, idx);

  EXPECT_EQ(map.Size(), 2);
  EXPECT_EQ(ptr.get(), nullptr);
}

TEST(TestConnectionMap, reuse) {
  ConnectionMap map(100);
  ConnectionDesc conn_desc("dbname", "username", "parameter");

  auto idx1 = map.Insert(conn_desc, ConnectionFactory::GetConnection(conn_desc));
  auto idx2 = map.Insert(conn_desc, ConnectionFactory::GetConnection(conn_desc));
  map.Delete(conn_desc, idx1);

  auto ptr = map.Get(conn_desc, idx2);
  auto reuse_ptr = map.Reuse(conn_desc);

  EXPECT_EQ(ptr.get(), reuse_ptr.get());
}