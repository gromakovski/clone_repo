#include "session.h"
#include <iostream>

void session::do_read() {
  auto self(shared_from_this());
  socket_.async_read_some(
      boost::asio::buffer(data_, max_length),
      [this, self](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
          // std::cout << data_;
          data_received(length);
          memset(data_, 0, max_length);
          do_read();
        }
      });
}

void session::data_received(std::size_t length) {
  bselector_.dataReceived(data_, length);
}
