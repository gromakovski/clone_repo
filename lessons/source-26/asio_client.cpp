#include <boost/asio.hpp>

#include <iostream>

namespace ba = boost::asio;

int main(int, char *[]) {

    ba::io_service service;

    ba::ip::tcp::endpoint ep(
    	ba::ip::address::from_string(
    		"127.0.0.1"
    	),
    	9999
    );
    ba::ip::tcp::socket sock(service);

    sock.connect(ep);

    ba::write(sock, ba::buffer("ping", 4));

    char data[4];
    size_t len = sock.read_some(
    	ba::buffer(data)
    );
    std::cout << "receive " << len << "=" << std::string{data, len} << std::endl;

    return 0;
}
