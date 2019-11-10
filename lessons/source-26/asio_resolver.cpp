#include <boost/asio.hpp>
#include <iostream>


namespace ba = boost::asio;


void test_sync_resolver() {
	std::cout << "\ntest_sync_resolver\n" << std::endl;

	ba::io_service service;
    ba::ip::tcp::resolver resolver{service};
    auto query = ba::ip::tcp::resolver::query{"google.com", "80"};

    auto iter = resolver.resolve(query);

    ba::ip::tcp::endpoint ep = *iter;

    std::cout << ep.address().to_string() << ":" << ep.port() << std::endl;

    std::cout << std::endl;
}


void test_async_resolver() {
	std::cout << "\ntest_async_resolver\n" << std::endl;

	ba::io_service service;
    ba::ip::tcp::resolver resolver{service};
    auto query = ba::ip::tcp::resolver::query{"google.com", "80"};

    resolver.async_resolve(
    	query,
    	[](const boost::system::error_code& ec, ba::ip::tcp::resolver::iterator iter) {
    		for (iter; iter != ba::ip::tcp::resolver::iterator{}; ++iter) {
    			ba::ip::tcp::endpoint ep = *iter;
    			std::cout << ep.address().to_string() << ":" << ep.port() << std::endl;
    		}
    	}
    );
    
    service.run();

	std::cout << std::endl;
}


int main(int, char *[]) {

    test_sync_resolver();

    test_async_resolver();

    return 0;
}
