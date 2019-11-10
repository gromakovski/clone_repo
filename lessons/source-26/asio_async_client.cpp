#include <boost/asio.hpp>

#include <array>
#include <iostream>
#include <string>
#include <thread>

namespace ba = boost::asio;

class AsyncClient {
public:
    AsyncClient(ba::io_service& io_service)
        : m_tcp_socket{io_service}
        , m_resolver{io_service} {

    }

    void get(const std::string& host, const std::string& service) {
        std::cout << "### get" << std::endl; 

        ba::ip::tcp::resolver::query query{host, service};

        m_resolver.async_resolve(
            query, 
            [&](const boost::system::error_code &ec, ba::ip::tcp::resolver::iterator it) {
                this->resolveHandler(ec, it);
            }
        );
    }

private:
    void resolveHandler(const boost::system::error_code &ec, ba::ip::tcp::resolver::iterator it) {
        std::cout << "### resolveHandler" << std::endl;
        if (ec) {
            std::cout << "resolveHandler - failed! err = " << ec.message() << std::endl;
            return;
        }

        m_tcp_socket.async_connect(
            *it, 
            [&](const boost::system::error_code &ec) {
                this->connectHandler(ec);
            }
        );
            
    }

    void connectHandler(const boost::system::error_code &ec) {
        std::cout << "### connectHandler" << std::endl;
        if (ec) {
            std::cout << "connectHandler - failed! err = " << ec.message() << std::endl;
            return;
        }

        const std::string request = "GET /notExists HTTP/1.1\r\n\r\n";
        ba::write(m_tcp_socket, ba::buffer(request));
        
        m_tcp_socket.async_read_some(
            ba::buffer(m_buffer),
            [&](const boost::system::error_code &ec, std::size_t bytes_transferred) {
                readHandler(ec, bytes_transferred);
            }
        );
    }

    void readHandler(const boost::system::error_code &ec, std::size_t bytes_transferred) {
        std::cout << "### readHandler" << std::endl;
        if (ec) {
            std::cout << "readHandler - failed! err = " << ec.message() << std::endl;
            return;
        }

        std::cout.write(m_buffer.data(), bytes_transferred);
        boost::asio::async_read(
            m_tcp_socket,
            ba::buffer(m_buffer),
            [&](const boost::system::error_code &ec, std::size_t bytes_transferred) {
                readHandler(ec, bytes_transferred);
            }
        );
    }

    ba::ip::tcp::resolver m_resolver;
    ba::ip::tcp::socket m_tcp_socket;
    std::array<char, 4096> m_buffer;

};

int main()
{
    ba::io_service io_service;

    AsyncClient client{ io_service };

    client.get("google.com", "http");

    io_service.run();    

    return 0;
}





