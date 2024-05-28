#ifndef QQ_TEST_CONNECTION_MOCK_SERVER_H_
#define QQ_TEST_CONNECTION_MOCK_SERVER_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <vector>
#include <chrono>

using boost::asio::ip::tcp;

namespace test {
class MockConnection : public std::enable_shared_from_this<MockConnection> {
 public:
  using Pointer = std::shared_ptr<MockConnection>;

  ~MockConnection() {
    socket_.close();
  }

  static Pointer Create(tcp::socket&& socket) {
    return Pointer(new MockConnection(std::move(socket)));
  } 

  void Start() {
    Read();
  }

 private:
  MockConnection(tcp::socket&& socket)
   : socket_(std::move(socket)),
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

  MockServer(boost::asio::io_context& io_context, const int port_number)
      : acceptor_(io_context, tcp::endpoint(tcp::v4(), port_number)),
        time_points_() {
    StartAccept();
  }

  void Stop() {
    connections_.clear();
    time_points_.clear();
    acceptor_.close();
  }

  const std::vector<TimePoint>& GetAcceptedRecord() const {
    return time_points_;
  }

 private:
  void StartAccept() {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
          if (!ec) {
            auto conn = MockConnection::Create(std::move(socket));
            time_points_.emplace_back(std::chrono::steady_clock::now());
            connections_.emplace_back(conn);
            conn->Start();
          }
        });
  }

  tcp::acceptor acceptor_;
  std::vector<TimePoint> time_points_;
  std::vector<MockConnection::Pointer> connections_;
};
}  // namespace test
#endif /* QQ_TEST_CONNECTION_MOCK_SERVER_H_ */