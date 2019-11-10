#include <atomic>
#include <iostream>
#include <thread>

#include <cassert>

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x() {
	x.store(true, std::memory_order_release);
}

void write_y() {
	y.store(true, std::memory_order_release);
}

void read_x_then_y() {
	while(!x.load(std::memory_order_acquire));
	if (y.load(std::memory_order_acquire))
		++z;
}

void read_y_then_x() {
	while(!y.load(std::memory_order_acquire));
	if (x.load(std::memory_order_acquire))
		++z;
}



int test() {
	x = false;
	y = false;
	z = 0;
	
	std::thread a(write_x);	
	std::thread b(write_y);	
	std::thread c(read_x_then_y);	
	std::thread d(read_y_then_x);
	
	a.join();
	b.join();
	c.join();
	d.join();
	
	assert(z.load() != 0); // Oooops

	return 0;
}


int notAtomic;

void write_x_then_y() {
    notAtomic = 42;
    x.store(true, std::memory_order_relaxed);
    y.store(true, std::memory_order_release);
}

void read_y_then_x2() {
    while(!y.load(std::memory_order_acquire));
    if (x.load(std::memory_order_relaxed))
        ++z;
    assert(notAtomic == 42);
}

void test2() {
    notAtomic = 0;
    x = false;
	y = false;
	z = 0;
	
	std::thread a(write_x);	
	std::thread b(write_y);	
	std::thread c(write_x_then_y);	
	std::thread d(read_y_then_x2);
	
	a.join();
	b.join();
	c.join();
	d.join();
	
	assert(z.load() != 0); // Oooops
}




int main() {
    return 0;
}