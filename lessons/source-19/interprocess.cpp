#include <iostream>
#include <string>
#include <thread>

#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

// Auto-removed
#include <boost/interprocess/windows_shared_memory.hpp>

// Managed
#include <boost/interprocess/managed_shared_memory.hpp>

#include <boost/interprocess/sync/named_mutex.hpp>

void test_shared_memory(bool isWriter) {
	boost::interprocess::shared_memory_object 
		shared{boost::interprocess::open_or_create, "MySharedObject", boost::interprocess::read_write};

	shared.truncate(100);

	std::cout << "name = " << shared.get_name() << std::endl;
	boost::interprocess::offset_t size;
	shared.get_size(size);
	std::cout << "size = " << size << std::endl;

	if (isWriter) {
		boost::interprocess::named_mutex mutex{boost::interprocess::open_or_create, "mtx"};

		std::cout << "Writer process. Writes...." << std::endl;

		boost::interprocess::mapped_region region{shared, boost::interprocess::read_write};
		std::cout << "read_write address = " << region.get_address() << std::endl;
		
		char * strPtr = static_cast<char*>(region.get_address());
		memcpy(strPtr, "Hello from other process!", sizeof("Hello from other process!"));
	}
	else {
		std::cout << "Reader process. Waiting...." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));

		boost::interprocess::mapped_region region_read_only{shared, boost::interprocess::read_only};
		std::cout << "region_read_only address = " << region_read_only.get_address() << std::endl;
	
		char *readStrPtr = static_cast<char*>(region_read_only.get_address());
		std::cout << "result = " << readStrPtr << std::endl;
	}

	if (isWriter) {
		std::cout << "Writer process. Waiting...." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(10));

		bool removed = boost::interprocess::shared_memory_object::remove("MySharedObject");
  		std::cout << std::boolalpha << removed << '\n';
	}

}

int main(int argc, char* argv[]) {
	test_shared_memory(argc == 1);

	return 0;
}