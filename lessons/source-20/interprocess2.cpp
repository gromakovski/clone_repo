#include <iostream>
#include <string>
#include <thread>

#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

// Auto-removed
//#include <boost/interprocess/windows_shared_memory.hpp>

// Managed
#include <boost/interprocess/managed_shared_memory.hpp>


const char * sharedMemoryName = "MySharedObject";
const char * sharedMutexName = "MySharedMutex";
const char * sharedConditionReadName = "MySharedConditionRead";
const char * sharedConditionWriteName = "MySharedConditionWrite";
const int COUNT = 10;

void reader() {
	std::cout << "Reader started!" << std::endl;

	boost::interprocess::shared_memory_object 
		memory{ 
			boost::interprocess::open_or_create, 
			sharedMemoryName, 
			boost::interprocess::read_write
		};
	memory.truncate(100);

	boost::interprocess::mapped_region 
		region_read_only{
			memory, 
			boost::interprocess::read_only
		};

	boost::interprocess::named_mutex 
		mutex{
			boost::interprocess::open_or_create, 
			sharedMutexName
		};

	boost::interprocess::named_condition 
		namedConditionRead{
			boost::interprocess::open_or_create,
			sharedConditionReadName
		};

	boost::interprocess::named_condition 
		namedConditionWrite{
			boost::interprocess::open_or_create,
			sharedConditionWriteName
		};

	for (int i = 0; i < COUNT; ++i) {
		boost::interprocess::scoped_lock<boost::interprocess::named_mutex> 
	  			lock{
	  				mutex
	  			};

	  	std::cout << "Reader - waiting..." << std::endl;
	  	namedConditionRead.wait(lock);

		char *readStrPtr = static_cast<char*>(region_read_only.get_address());
		std::cout << "result[" << i << "] = " << readStrPtr << std::endl;

		std::cout << "Reader - notify" << std::endl;
		namedConditionWrite.notify_all();
	}
	namedConditionWrite.notify_all();
}

void writer() {
	std::cout << "Writer started!" << std::endl;

	boost::interprocess::shared_memory_object 
		memory{ 
			boost::interprocess::open_or_create, 
			sharedMemoryName, 
			boost::interprocess::read_write
		};
	memory.truncate(100);


	boost::interprocess::mapped_region 
		region{
			memory, 
			boost::interprocess::read_write
		};

	boost::interprocess::named_mutex 
		mutex{
			boost::interprocess::open_or_create, 
			sharedMutexName
		};

	boost::interprocess::named_condition 
		namedConditionRead{
			boost::interprocess::open_or_create,
			sharedConditionReadName
		};

	boost::interprocess::named_condition 
		namedConditionWrite{
			boost::interprocess::open_or_create,
			sharedConditionWriteName
		};

	for (int i = 0; i < COUNT; ++i) {
		{
			boost::interprocess::scoped_lock<boost::interprocess::named_mutex> 
	  			lock{
	  				mutex
	  			};

			char * strPtr = static_cast<char*>(region.get_address());
			
			const std::string iteration = std::to_string(i);
			memcpy(strPtr, iteration.data(), iteration.size() + 1);
			
			strPtr += iteration.size();
			memcpy(strPtr, "Hello from other process!", sizeof("Hello from other process!"));

			std::cout << "[" << i << "] Writer notify" << std::endl;
			namedConditionRead.notify_all();
		}
		{
			boost::interprocess::scoped_lock<boost::interprocess::named_mutex> 
	  			lock{
	  				mutex
	  			};

	  		std::cout << "[" << i << "] Writer waiting..." << std::endl;
			namedConditionWrite.wait(lock);
		}	

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	bool removed = boost::interprocess::shared_memory_object::remove(sharedMemoryName);
	bool removed2 = boost::interprocess::named_mutex::remove(sharedMutexName);
	bool removed3 = boost::interprocess::named_mutex::remove(sharedConditionReadName);
	bool removed4 = boost::interprocess::named_mutex::remove(sharedConditionWriteName);
}

int main(int argc, char* argv[]) {
	if (argc == 1)
		writer();
	else
		reader();

	return 0;
}