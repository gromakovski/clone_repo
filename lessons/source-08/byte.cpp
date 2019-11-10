#include <array>
#include <bitset>
#include <cstddef>
#include <iostream>


namespace {
	// Like char and unsigned char, it can be used to access 
	// raw memory occupied by other objects (object representation), 
	// but unlike those types, it is not a character type and 
	// is not an arithmetic type. 
	// A byte is only a collection of bits, and the only operators 
	// defined for it are the bitwise ones. 

	// std::byte implementation
	enum class byte : unsigned char {
	};
}

void c_style_func([[maybe_unused]] char * data) {
	// do something with data
}

void print_bin(std::byte value) {
	std::bitset<8> bitset{std::to_integer<uint8_t>(value)};
	std::cout << "0b" << bitset << std::endl;
}

int main() {
	// Compile error
	// cannot convert 'int' to 'std::byte' in initialization
    // std::array<std::byte, 5> values = {0, 1, 2, 3, 4};

	// Compile error 
	// for (std::byte i = 0; i < 5; ++i)
	// 	values[i] = i;

	// Compile error
	// no match for 'operator++' (operand type is 'std::byte')
	// for (std::byte i = std::byte{0}; i < std::byte{5}; ++i)
	// 	values[i] = i;

	[[maybe_unused]] std::array<std::byte, 5> values2 = 
		{std::byte{0}, std::byte{1}, std::byte{2}, std::byte{3}, std::byte{4}};

	// Compile error
	// cannot convert 'std::byte*' to 'char*'
    // c_style_func(values2.data());

    auto b = std::byte{0b11001100};
    std::cout << "b = ";
    print_bin(b);

    std::cout << "b | std::byte{0b00110011} = ";
    print_bin(b | std::byte{0b00110011});

    std::cout << "b & std::byte{0b00110011} = ";
    print_bin(b & std::byte{0b00110011});

    std::cout << "b ^ b = ";
    print_bin(b ^ b);

    std::cout << "b >> 2 = ";
	print_bin(b >> 2);

	std::cout << "b << 2 = ";
	print_bin(b << 2);

    return 0;
}