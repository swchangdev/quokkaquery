#ifndef QQ_TEST_CONNECTION_MOCK_SERVER_H_
#define QQ_TEST_CONNECTION_MOCK_SERVER_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <iomanip>
#include <vector>
#include <chrono>

using boost::asio::ip::tcp;

namespace test {
class MockConnection : public std::enable_shared_from_this<MockConnection> {
 public:
  using Pointer = std::shared_ptr<MockConnection>;

  static Pointer Create(boost::asio::io_context& io_context) {
    return Pointer(new MockConnection(io_context));
  } 

  void Start() {
    Read();
  }

  tcp::socket& Socket() {
    return socket_;
  }

 private:
  MockConnection(boost::asio::io_context& io_context)
   : socket_(io_context),
     read_buffer_(READ_BUFFER_MAX_SIZE) {}

  void Read() {
    auto self(shared_from_this());
    socket_.async_read_some(
      boost::asio::buffer(read_buffer_, READ_BUFFER_MAX_SIZE),
      [this, self](boost::system::error_code ec, std::size_t length) {
        if (!ec && length > 0) {
          Write(length);
        }
      }
    );
  }

  void Write(std::size_t length) {
    auto self(shared_from_this());
    boost::asio::async_write(
      socket_,
      boost::asio::buffer(read_buffer_, length),
      [this, self](boost::system::error_code ec, std::size_t) {
        if (!ec) {
          Read();
        }
      }
    );
  }

  const int READ_BUFFER_MAX_SIZE = 1024;
  tcp::socket socket_;
  std::vector<char> read_buffer_;
};

class MockServer {
 public:
  using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

  explicit MockServer(const int port_number)
   : io_context_(),
     acceptor_(io_context_, tcp::endpoint(tcp::v4(), port_number)),
     time_points_() {
    StartAccept();
  }

  void Run() {
    io_context_.run();
  }

  void Stop() {
    for (auto &conn : connections_) {
      conn->Socket().close();
    }
    connections_.clear();
    time_points_.clear();
    io_context_.stop();
  }

  const std::vector<TimePoint>& GetAcceptedRecord() const {
    return time_points_;
  }

 private:
  void StartAccept() {
    auto new_connection = MockConnection::Create(io_context_);
    acceptor_.async_accept(
      new_connection->Socket(), 
      boost::bind(&MockServer::HandleAccept, this, new_connection,
                  boost::asio::placeholders::error)
    );
  }

  void HandleAccept(MockConnection::Pointer conn, const boost::system::error_code& error) {
    if (!error) {
      time_points_.emplace_back(std::chrono::steady_clock::now());
      connections_.emplace_back(conn);
      conn->Start();
    }
  }

  boost::asio::io_context io_context_;
  tcp::acceptor acceptor_;
  std::vector<TimePoint> time_points_;
  std::vector<MockConnection::Pointer> connections_;
};
}  // namespace test
#endif /* QQ_TEST_CONNECTION_MOCK_SERVER_H_ */