#include <atomic>
#include <iostream>
#include <thread>

#include <cassert>

namespace naive {

	int globalValue{0};

	void workerFunction() {
		++globalValue;
	}
	
	void test() {
		std::thread worker1{workerFunction};
		std::thread worker2{workerFunction};

		worker1.join();
		worker2.join();
	}
}


namespace race {

	int globalValue{0};
	std::atomic<bool> startFlag{false};

	void workerFunction() {
		while(!startFlag);
		++globalValue;
	}
	
	void test() {
		std::thread worker1{workerFunction};
		std::thread worker2{workerFunction};

		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		startFlag = true;

		worker1.join();
		worker2.join();
	}

}

namespace atomic {

	// Compile error
	// std::atomic<int> globalValue = 0;
	// use of deleted function ‘std::atomic<int>::atomic(const std::atomic<int>&)
	// std::atomic<int> globalValue{0};
	std::atomic<int> globalValue = 0;
	std::atomic<bool> startFlag{false};

	void workerFunction() {
		while(!startFlag);
		++globalValue;
	}
	
	void test() {
		std::thread worker1{workerFunction};
		std::thread worker2{workerFunction};

		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		startFlag = true;

		worker1.join();
		worker2.join();
	}

}

int main() {

	naive::test();
	std::cout << "naive result = " << naive::globalValue << std::endl;

	race::test();
	std::cout << "race result = " << race::globalValue << std::endl;

	atomic::test();
	std::cout << "atomic result = " << atomic::globalValue << std::endl;

	return 0;
}