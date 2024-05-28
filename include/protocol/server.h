#ifndef QQ_PROTOCOL_SERVER_H_
#define QQ_PROTOCOL_SERVER_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace quokkaquery {
namespace protocol {
namespace impl {
using tcp = boost::asio::ip::tcp;
}  // namespace impl
class Server {
 public:
  Server(boost::asio::io_context&, const int port_number);
  ~Server();

  impl::tcp::socket Accept();
  void Close();

 private:
  impl::tcp::acceptor acceptor_;
};
}  // namespace protocol
}  // namespace quokkaquery

#endif /* QQ_PROTOCOL_SERVER_H_ */