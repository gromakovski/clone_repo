#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include "async.h"
#include "session.h"

class server {
 public:
  server(short port);

 private:
  void do_accept();

  boost::asio::io_service io_service_;
  tcp::acceptor acceptor_;
  tcp::socket socket_;

  async::handle_t bulkParserHandler_;
};

#endif  // SERVER_H
