#include <boost/asio.hpp>

#include <iostream>
#include <thread>


namespace ba = boost::asio;

void client_session(ba::ip::tcp::socket sock) {
    while (true) {
        try {
            char data[4];
            size_t len = sock.read_some(ba::buffer(data));
            std::cout << "receive " << len << "=" << std::string{data, len} << std::endl;
            ba::write(sock, ba::buffer("pong", 4));
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            break;
        }
    }
}

int main(int, char *[]) {

    ba::io_service service;
    ba::ip::tcp::endpoint ep(
        ba::ip::tcp::v4(), 
        9999
    );
    
    ba::ip::tcp::acceptor acc(service, ep);
    while (true) {
        auto sock = ba::ip::tcp::socket(service);
        acc.accept(sock);
        std::thread(client_session, std::move(sock)).detach();
    }

    return 0;
}
