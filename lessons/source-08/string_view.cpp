#include <iostream>
#include <string_view>

void func(std::string_view view) {
	std::cout << view << std::endl;
	std::cout << view.substr(0, 2) << std::endl;
	std::cout << view.find('a') << std::endl;
}

std::string_view getSubstring(std::string_view view) {
	return view.substr(0, 2);
}

std::string_view getSubstringWrong(const std::string& str) {
	std::string value = "trololo" + str;
	return value.substr(0, 2);
}


int main() {
	func("abcdefgh");

	const std::string str = "hgfedcba";
	func(str);

	func(str.c_str());

	const char * str2 = "abcdefgh";
	auto result = getSubstring(str2);
	std::cout << result << std::endl;
	std::cout << std::hex << (void*)str2 << std::endl;
	std::cout << std::hex << (void*)result.data() << std::endl;

	// oops
	std::cout << getSubstringWrong(str) << std::endl;

	return 0;
}