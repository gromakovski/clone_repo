#include <array>
#include <charconv>
#include <iostream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

namespace impl {
	struct to_chars_result {
	    char* ptr;
	    std::errc ec;
	};

	struct from_chars_result {
	    const char* ptr;
	    std::errc ec;
	};

	enum class chars_format {

	    scientific = /*unspecified*/0,
	    fixed = /*unspecified*/1,
	    hex = /*unspecified*/2,
	    general = fixed | scientific
	};

	// from_chars_result from_chars(const char* first, const char* last,
    //                               /*see below*/int& value, int base = 10/* ... 35 */); 

	// from_chars_result from_chars(const char* first, const char* last, float& value,
    //                               chars_format fmt = chars_format::general);

	// from_chars_result from_chars(const char* first, const char* last, double& value,
    //                               chars_format fmt = chars_format::general);

	// from_chars_result from_chars(const char* first, const char* last, long double& value,
    //                               chars_format fmt = chars_format::general);
}

void basic_example() {
	std::array<char, 10> buffer;

	{
		auto [ptr, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), 1005000000);
		if (ec == std::errc()) {
			std::cout << "success!" << std::endl;
			std::cout << std::string_view(buffer.data(), ptr - buffer.data()) << std::endl;
		} else {
			auto errCode = std::make_error_code(ec);
			std::cout << errCode.message() << std::endl;
		}
	}

	{
		int value;
		auto [ptr, ec] = std::from_chars(buffer.data(), buffer.data() + buffer.size(), value);
		if (ec == std::errc()) {
			std::cout << "success!" << std::endl;
			std::cout << value << std::endl;
		} else {
			auto errCode = std::make_error_code(ec);
			std::cout << errCode.message() << std::endl;
		}
	}
}

void strange_example() {

	std::vector<std::pair<int, std::string>> values = {
		{10, "-123dkasd"},
		{10, "+123"},
		{16, "0xabcd"},
		{16, "0XABCD"},
		{16, "0xABCD"}
	};
	
	for (const auto& value : values) {
		const auto& [base, str] = value;

		std::cout << "Next check: base = " << base << " str = " << str << std::endl;
		int value;
		auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value, base);
		if (ec == std::errc()) {
			std::cout << "success! value = " << value << std::endl;
		} else {
			auto errCode = std::make_error_code(ec);
			std::cout << errCode.message() << std::endl;
		}
		std::cout << "lost: " << std::string_view(ptr, str.data() + str.size() - ptr) << std::endl;
		std::cout << std::endl;
	}
}

int main() {
	basic_example();

	strange_example();

	return 0;
}
