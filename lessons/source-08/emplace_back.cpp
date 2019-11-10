#include <iostream>
#include <string>
#include <vector>


int main() {
	int counter = 0;

	std::vector<std::string> strings;

	strings.emplace_back("number: " + std::to_string(counter++));
	std::cout << strings.back() << std::endl;

	std::cout << strings.emplace_back("number: " + std::to_string(counter++)) << std::endl;

	return 0;
}