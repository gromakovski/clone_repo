#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

std::atomic<bool> finished{false};
std::mutex conditionMutex;
std::condition_variable condition;

std::vector<int> data;

void consumer() {
	while(!finished) {
		std::unique_lock<std::mutex> lck{conditionMutex};
		while(data.empty() && !finished) condition.wait(lck);

		std::cout << "Consumer - next data to proceed!\n";
		for (auto& v : data)
			std::cout << v << ' ';
		std::cout << std::endl;

		data.clear();
	}

	std::cout << "Consumer - finished!" << std::endl;
}

void producer() {
	const int step = 5;
	int counter = 0;
	while(!finished) {
		{
			std::lock_guard<std::mutex> guard{conditionMutex};
			std::cout << "Producer - generate data" << std::endl;
			for (int i = 0; i < step; ++i)
				data.emplace_back(++counter);
			condition.notify_one();
		}
		
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	condition.notify_one();

	std::cout << "Producer - finished!" << std::endl;
}


void test_condition() {

	std::thread consumerThread{consumer};
	std::thread producerThread{producer};

	std::this_thread::sleep_for(std::chrono::seconds(10));

	finished = true;
	producerThread.join();
	consumerThread.join();

}

int main() {

	test_condition();

	return 0;
}