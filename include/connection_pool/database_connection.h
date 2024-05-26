#ifndef QQ_CP_DATABASE_CONNECTION_H_
#define QQ_CP_DATABASE_CONNECTION_H_

#include <boost/asio.hpp>
#include <vector>
#include <string>

namespace quokkaquery {
namespace cp {
struct DatabaseDesc {
  const std::string ip_addr;
  const std::string port;
};

class DatabaseConnection {
 public:
  using BufferType = std::vector<char>;

  DatabaseConnection(const DatabaseDesc&);
  ~DatabaseConnection();

  const std::size_t Write(const BufferType& message);
  const std::size_t Read(const std::size_t size);
  const BufferType& GetReadBuffer() const;

 private:
  boost::asio::io_context io_context_;
  boost::asio::ip::tcp::socket socket_;
  BufferType read_buffer_;
};
}  // namespace cp
}  // namespace quokkaquery

#endif /* QQ_CP_DATABASE_CONNECTION_H_ */