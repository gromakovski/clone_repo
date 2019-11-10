#include <atomic>
#include <iostream>
#include <thread>

namespace test1 {
	void testInterface() {
		std::cout << "\ntestInterface\n";

		// Yes, it is a define. 
		std::atomic_flag atomicFlag = ATOMIC_FLAG_INIT;
		
		bool isSet = atomicFlag.test_and_set();
		std::cout << "after initialize isSet = " << std::boolalpha << isSet << std::endl;
		
		isSet = atomicFlag.test_and_set();
		std::cout << "after set isSet = " << std::boolalpha << isSet << std::endl;

		atomicFlag.clear();
		
		isSet = atomicFlag.test_and_set();
		std::cout << "after clear isSet = " << std::boolalpha << isSet << std::endl;

		std::cout << std::endl;
	}
}

namespace test2 {
	class SpinlockMutex {
	public:
		SpinlockMutex() :
			m_flag{ATOMIC_FLAG_INIT} {

		}

		void lock() {
			while(m_flag.test_and_set());
		}

		void unlock() {
			m_flag.clear();
		}

	private:
		std::atomic_flag m_flag;
	};

	void testSpinlockMutex() {
		std::cout << "\ntestSpinlockMutex\n";

		SpinlockMutex spinlockMutex;

		auto workerFunc = [&spinlockMutex]() {
			const auto id = std::this_thread::get_id();

			std::cout << '[' << id << "] - locking..." << std::endl;
			spinlockMutex.lock();
			
			std::cout << '[' << id << "] - under lock..." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			
			std::cout << '[' << id << "] - unlocking..." << std::endl;
			spinlockMutex.unlock();
			
		};

		std::thread worker1{workerFunc};
		std::thread worker2{workerFunc};

		worker1.join();
		worker2.join();

		std::cout << std::endl;
	}
}


int main() {
	test1::testInterface();
	test2::testSpinlockMutex();

	return 0;
}