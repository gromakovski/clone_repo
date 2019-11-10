#include <future>
#include <iostream>
#include <thread>

void test_promise() {

	auto worker = [](int value, std::promise<int>& promise) {
		try {
			if (value == 7)
				throw std::logic_error("Ooooops");

			promise.set_value(42 + value);
		}
		catch(const std::exception& ex) {
			promise.set_exception(std::current_exception());
		}
	};

	std::promise<int> promise1;
	std::future<int> result1 = promise1.get_future();

	std::thread thread1{worker, 7, std::ref(promise1)};

	try {
		std::cout << "Waiting...." << std::endl;
		result1.wait();
		std::cout << "Result!" << std::endl;
		auto value1 = result1.get();
		std::cout << "value1 = " << value1 << std::endl;
	}
	catch(const std::exception& ex) {
		std::cout << "Exception! " << ex.what() << std::endl;
	}
	thread1.join();


	std::promise<int> promise2;
	std::future<int> result2 = promise2.get_future();

	std::thread thread2{worker, 10, std::ref(promise2)};

	auto value2 = result2.get();
	std::cout << "value2 = " << value2 << std::endl;

	thread2.join();

}


int main() {

	test_promise();

	return 0;
}