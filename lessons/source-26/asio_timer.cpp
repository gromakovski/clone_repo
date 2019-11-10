#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <chrono>
#include <iostream>
#include <thread>

void test_timer_async() {
	std::cout << "\ntest_timer_async\n" << std::endl;

	// New style
	// boost::asio::io_context io_context;

	boost::asio::io_service io_service;
	boost::asio::steady_timer timer{
		io_service,
		std::chrono::seconds{1}
	};
	timer.async_wait(
		[](const boost::system::error_code&) {
			std::cout << "Hello from async timeout!" << std::endl;
		}
	);

	io_service.run();

	std::cout << std::endl;
}


void test_two_timers_async() {
	std::cout << "\ntest_two_timers_async\n" << std::endl;

	boost::asio::io_service io_service;
	
	boost::asio::steady_timer timer1{
		io_service,
		std::chrono::seconds{1}
	};
	timer1.async_wait(
		[](const boost::system::error_code&) {
			std::cout << "Hello from async timeout1!" << std::endl;
		}
	);

	boost::asio::steady_timer timer2{
		io_service,
		std::chrono::seconds{1}
	};
	timer2.async_wait(
		[](const boost::system::error_code&) {
			std::cout << "Hello from async timeout2!" << std::endl;
		}
	);

	io_service.run();

	std::cout << std::endl;
}

void test_timer_sync() {
	std::cout << "\ntest_timer_sync\n" << std::endl;

	boost::asio::io_service io_service;
	boost::asio::steady_timer timer{
		io_service,
		std::chrono::seconds{1}
	};
	boost::system::error_code errCode;
	timer.wait(errCode);
	std::cout << "After timeout!" << std::endl;

	std::cout << std::endl;
}


void test_timer_async_wich_thread() {
	std::cout << "\ntest_timer_async_wich_thread\n" << std::endl;

	boost::asio::io_service io_service;
	boost::asio::steady_timer timer{
		io_service,
		std::chrono::seconds{1}
	};
	timer.async_wait(
		[](const boost::system::error_code&) {
			std::cout << std::this_thread::get_id() << " Hello from async timeout!" << std::endl;
		}
	);

	std::cout << std::this_thread::get_id() << " io_service.run" << std::endl;
	io_service.run();

	std::cout << std::endl;
}

void timeoutFunction(const boost::system::error_code&, int value) {
	std::cout << "Hello from timeoutFunction with value = " << value << std::endl;
}

void test_timer_async_args() {
	std::cout << "\ntest_timer_async_args\n" << std::endl;

	boost::asio::io_service io_service;
	boost::asio::steady_timer timer{
		io_service,
		std::chrono::seconds{1}
	};

	int arg = 42;
	timer.async_wait(
		[&arg](const boost::system::error_code& err) {
			timeoutFunction(err, arg);
		}
	);

	io_service.run();

	std::cout << std::endl;
}

void test_two_threads() {
	std::cout << "\ntest_two_timers_async\n" << std::endl;

	boost::asio::io_service io_service;
	
	boost::asio::steady_timer timer1{
		io_service,
		std::chrono::seconds{1}
	};
	timer1.async_wait(
		[](const boost::system::error_code&) {
			std::cout << std::this_thread::get_id() << " Hello from async timeout1!" << std::endl;
		}
	);

	boost::asio::steady_timer timer2{
		io_service,
		std::chrono::seconds{1}
	};
	timer2.async_wait(
		[](const boost::system::error_code&) {
			std::cout << std::this_thread::get_id() << " Hello from async timeout2!" << std::endl;
		}
	);

	std::thread thread1{
		[&io_service]() { io_service.run(); }
	};
	std::thread thread2{
		[&io_service]() { io_service.run(); }
	};

	thread1.join();
	thread2.join();

	std::cout << std::endl;
}


int main()
{
	test_timer_async();
	test_two_timers_async();
	test_timer_sync();
	test_timer_async_wich_thread();
	test_timer_async_args();
	test_two_threads();

	return 0;
}