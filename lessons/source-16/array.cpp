#include <array>
#include <iostream>

void testPlacing() {
	std::cout << "\ntestPlacing\n";

	int stackVariable = 0;
	std::array<int, 10> values = {0, 1, 2, 3};

	std::cout << "&stackVariable = " << &stackVariable << std::endl;
	std::cout << "&values        = " << &values << std::endl;
	std::cout << "values.data()  = " << values.data() << std::endl;

	for(auto& v : values)
		std::cout << v << ' ';
	std::cout << std::endl;
}

void testIterator() {
	std::cout << "\ntestIterator\n";

	std::array<int, 10> values = {0, 1, 2, 3, 4, 5, 6, 7, 8};

	auto iter = std::next(values.cbegin(), 3);
	std::cout << *iter << std::endl;

	++iter;
	std::cout << *iter << std::endl;

	--iter;
	--iter;
	std::cout << *iter << std::endl;

	iter += 3;
	std::cout << *iter << std::endl;
}

int main() {
	testPlacing();
	testIterator();

	return 0;
}