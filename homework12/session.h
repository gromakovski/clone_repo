#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include "builder_selector.h"

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {
 public:
  session(tcp::socket socket, async::handle_t bulkParserHandler)
      : socket_(std::move(socket)), bselector_(bulkParserHandler) {}

  void start() { do_read(); }

 private:
  void do_read();
  void data_received(std::size_t length);

  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];

  BuilderSelector bselector_;
};

#endif  // SESSION_H
