#include "server.h"
#include <iostream>
#include "session.h"

#include "async.h"

server::server(short port)
    : acceptor_(io_service_, tcp::endpoint(tcp::v4(), port)),
      socket_(io_service_) {
  std::size_t bulk = 3;
  bulkParserHandler_ = async::connect(bulk);

  do_accept();
  io_service_.run();
}

void server::do_accept() {
  acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
    if (!ec) {
      std::make_shared<session>(std::move(socket_), bulkParserHandler_)
          ->start();
    }

    do_accept();
  });
}
