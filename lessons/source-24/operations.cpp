#include <atomic>
#include <iostream>

#include <cassert>

void test_bool() {
	std::cout << "\n************\ntest_bool\n";

	std::atomic<bool> atomicBool; // value is undefined - as always

	// Compile error:
	// use of deleted function 'std::atomic<bool>::atomic(const std::atomic<bool>&)'
	// std::atomic<bool> other{atomicBool};

	// std::atomic<bool> other;
	// Compile error:
	// use of deleted function 'std::atomic<bool>& std::atomic<bool>::operator=(const std::atomic<bool>&)'
	// other = atomicBool;

	std::cout << "is_lock_free = " << std::boolalpha << atomicBool.is_lock_free() << std::endl;

	atomicBool.store(true); // atomic store without return value
	bool current = atomicBool.load(); // atomic load
	assert(current == true);

	atomicBool = true; // just assign. also atomic

	atomicBool = 0; // assing with cast 0 to bool
	assert(atomicBool == false); // cast to bool

	// Return value is not atomic, but simple bool
	bool newValue = atomicBool = true;
	assert(newValue == true);
	std::cout << "newValue = " << std::boolalpha << newValue << std::endl;

	bool previousValue = atomicBool.exchange(false);
	assert(previousValue == true);
	std::cout << "previousValue = " << std::boolalpha << previousValue << std::endl;

	std::cout << std::endl;

	bool expected = atomicBool;
	const bool desired = true;
	bool exchanged = atomicBool.compare_exchange_strong(expected, desired);
	std::cout << "exchanged = " << std::boolalpha << exchanged << std::endl;
	std::cout << "expected = " << std::boolalpha << expected << std::endl;

	std::cout << std::endl;

	exchanged = atomicBool.compare_exchange_strong(expected, desired);
	std::cout << "exchanged = " << std::boolalpha << exchanged << std::endl;
	std::cout << "expected = " << std::boolalpha << expected << std::endl;

	std::cout << std::endl;
}

void test_pointer() {
	std::cout << "\n************\ntest_pointer\n";

	int array[] = {0, 1, 2, 3, 4, 5, 6};
	std::atomic<int*> atomicPtr{&array[0]};

	std::cout << "is_lock_free = " << std::boolalpha << atomicPtr.is_lock_free() << std::endl;

	// Load
	int * current = atomicPtr.load();
	assert(current == &array[0]);

	// Store
	atomicPtr.store(&array[0]);

	current = atomicPtr; // just read - also atomic

	atomicPtr = current; // just assign - also atomic

	atomicPtr.exchange(current);
	atomicPtr.compare_exchange_strong(current, current);


	int * previous = nullptr;
	previous = atomicPtr.fetch_add(1); 
	assert(previous == &array[0]);
	assert(atomicPtr == &array[1]);

	previous = atomicPtr.fetch_sub(1);
	assert(previous == &array[1]);
	assert(atomicPtr == &array[0]);

	atomicPtr++;
	assert(atomicPtr == &array[1]);

	atomicPtr--;
	assert(atomicPtr == &array[0]);

	atomicPtr += 1;
	assert(atomicPtr == &array[1]);

	atomicPtr -= 1;
	assert(atomicPtr == &array[0]);

	// Not the same as += 1 !!!
	// Not atomic operation, but 3 atomic operations:
	// 1 - read current value atomicPtr
	// 2 - get new value atomicPtr + 1
	// 3 - place new value to atomicPtr
	atomicPtr = atomicPtr + 1;
	assert(atomicPtr == &array[1]);

	// Compile error - no operator&=
	// atomicPtr &= 1;

	std::cout << std::endl;
}


void test_int() {
	std::cout << "\n************\ntest_int\n";

	std::atomic<int> atomicInt{42};

	std::cout << "is_lock_free = " << std::boolalpha << atomicInt.is_lock_free() << std::endl;

	// load
	// store
	// compare_exchange_strong
	// compare_exchange_weak - a bit later
	// fetch_add
	// fetch_sub

	int previous = atomicInt.fetch_and(2); // 0b101010 & 0b10
	assert(previous == 42);
	assert(atomicInt == 2);

	previous = atomicInt.fetch_or(3); // 0b10 | 0b11
	assert(previous == 2);
	assert(atomicInt == 3);	

	previous = atomicInt.fetch_xor(3);
	assert(previous == 3);
	assert(atomicInt == 0);

	atomicInt &= 2;
	atomicInt |= 2;
	atomicInt ^= 2;

	// Compile error
	// no match for ‘operator*=’
	// atomicInt *= 2;

	// Possible, but not atomic - Read-Modify-Write
	atomicInt = atomicInt * 2;

	std::cout << std::endl;
}


void test_custom() {
	std::cout << "\n************\ntest_custom\n";

	std::atomic<uint64_t> bigAtomic;
	std::cout << "bigAtomic is_lock_free = " << std::boolalpha << bigAtomic.is_lock_free() << std::endl;

	struct ByteStruct {
		uint8_t value;
	};
	std::atomic<ByteStruct> byteAtomic;
	std::cout << "byteAtomic is_lock_free = " << std::boolalpha << byteAtomic.is_lock_free() << std::endl;	

	struct TwoBytesStruct {
		uint8_t value;
		uint8_t value2;
	};
	std::atomic<TwoBytesStruct> twoBytesAtomic;
	std::cout << "twoBytesAtomic is_lock_free = " << std::boolalpha << twoBytesAtomic.is_lock_free() << std::endl;	

	// lib atomic is required
	struct ThreeBytesStruct {
		uint8_t value;
		uint8_t value2;
		uint8_t value3;
	};
	std::atomic<ThreeBytesStruct> threeBytesAtomic;
	std::cout << "threeBytesAtomic is_lock_free = " << std::boolalpha << threeBytesAtomic.is_lock_free() << std::endl;

	struct FourBytesStruct {
		uint8_t value;
		uint8_t value2;
		uint8_t value3;
		uint8_t value4;
	};
	std::atomic<FourBytesStruct> fourBytesAtomic;
	std::cout << "fourBytesAtomic is_lock_free = " << std::boolalpha << fourBytesAtomic.is_lock_free() << std::endl;

	// lib atomic is required
	struct SevenBytesStruct {
		uint8_t value;
		uint8_t value2;
		uint8_t value3;
		uint8_t value4;
		uint8_t value5;
		uint8_t value6;
		uint8_t value7;
	};
	std::atomic<SevenBytesStruct> sevenBytesAtomic;
	std::cout << "sevenBytesAtomic is_lock_free = " << std::boolalpha << sevenBytesAtomic.is_lock_free() << std::endl;

	struct SixteenBytesStruct {
		uint16_t value;
		uint16_t value2;
		uint16_t value3;
		uint16_t value4;
		uint16_t value5;
		uint16_t value6;
		uint16_t value7;
		uint16_t value8;
	};
	std::atomic<SixteenBytesStruct> sixteenBytesAtomic;
	std::cout << "sixteenBytesAtomic is_lock_free = " << std::boolalpha << sixteenBytesAtomic.is_lock_free() << std::endl;

	struct OtherFourBytesStruct {
		uint8_t value;
		uint16_t value2;
		uint8_t value3;
	};
	std::atomic<OtherFourBytesStruct> otherFourBytesAtomic;
	std::cout << "otherFourBytesAtomic is_lock_free = " << std::boolalpha << otherFourBytesAtomic.is_lock_free() << std::endl;

	std::cout << std::endl;
}


int main() {
	test_bool();
	test_pointer();
	test_int();
	test_custom();

	return 0;
}