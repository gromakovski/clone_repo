#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

const uint64_t count = 1'000'000;

class ScopedTimer {
	using TClock = std::chrono::high_resolution_clock;
	TClock::time_point m_start;
public:
	ScopedTimer() :
		m_start(TClock::now()) {

	}

	~ScopedTimer() {
		auto now = TClock::now();
		auto duration = now - m_start;
		std::cout << "duration = " 
			<< std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() 
			<< "ms" << std::endl;
	}

};


void test_without_synchronization(int threadCount) {
	std::cout << "\ntest_without_synchronization\n";
	std::cout << "threadCount = " << threadCount << '\n';

	ScopedTimer timer;

	std::atomic<bool> start{false};
	uint64_t sum = 0;

	auto workerFunc = [&start, &sum]() {
		while(!start);

		for (uint64_t i=0; i<count; ++i)
			sum += i;
	};

	std::vector<std::thread> threads;
	for (int i=0; i<threadCount; ++i) {
		threads.emplace_back(workerFunc);
	}

	start = true;

	for (auto& thr : threads)
		thr.join();

	std::cout << "result sum = " << sum << std::endl;

	std::cout << std::endl;
}


void test_with_mutex(int threadCount) {
	std::cout << "\ntest_with_mutex\n";
	std::cout << "threadCount = " << threadCount << '\n';

	ScopedTimer timer;

	std::mutex mutex;
	std::atomic<bool> start{false};
	uint64_t sum = 0;

	auto workerFunc = [&start, &sum, &mutex]() {
		while(!start);

		for (uint64_t i=0; i<count; ++i) {
			std::lock_guard<std::mutex> guard{mutex};
			sum += i;
		}
	};

	std::vector<std::thread> threads;
	for (int i=0; i<threadCount; ++i) {
		threads.emplace_back(workerFunc);
	}

	start = true;

	for (auto& thr : threads)
		thr.join();

	std::cout << "result sum = " << sum << std::endl;

	std::cout << std::endl;
}


void test_with_atomic(int threadCount) {
	std::cout << "\ntest_with_atomic\n";
	std::cout << "threadCount = " << threadCount << '\n';

	ScopedTimer timer;

	std::atomic<bool> start{false};
	std::atomic<uint64_t> sum{0};

	auto workerFunc = [&start, &sum]() {
		while(!start);

		for (uint64_t i=0; i<count; ++i) {
			sum += i;
		}
	};

	std::vector<std::thread> threads;
	for (int i=0; i<threadCount; ++i) {
		threads.emplace_back(workerFunc);
	}

	start = true;

	for (auto& thr : threads)
		thr.join();

	std::cout << "result sum = " << sum << std::endl;

	std::cout << std::endl;
}


int main() {
	test_without_synchronization(1);
	test_with_mutex(1);
	test_with_atomic(1);

	test_without_synchronization(4);
	test_with_mutex(4);
	test_with_atomic(4);

	test_without_synchronization(16);
	test_with_mutex(16);
	test_with_atomic(16);

	return 0;
}