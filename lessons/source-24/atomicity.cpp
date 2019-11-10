#include <iostream>
#include <stdexcept>
#include <string>

#include <cstring>

class SomeBadClass {
public:
	SomeBadClass() = default;

	void initialize_length(std::size_t size);

	void initialize_pointer(const char *str);

	void initialize_initialized();

	std::string getString();

private:
	bool m_initialized = false;
	char * m_data = nullptr;
	std::size_t m_size = 0;
};

void SomeBadClass::initialize_length(std::size_t size) {
	m_size = size;
}

void SomeBadClass::initialize_pointer(const char *str) {
	if (!m_size)
		throw std::logic_error("Size was not initialized!");
	m_data = new char[m_size];
	memcpy(m_data, str, m_size);
}

void SomeBadClass::initialize_initialized() {
	if (!m_size || !m_data)
		throw std::logic_error("Size or data were not initialized!");

	m_initialized = true;
}

std::string SomeBadClass::getString() {
	if (!m_initialized)
		throw std::logic_error("Object was not initialized!");

	return m_data;
}


void correctUsage() {
	const char * str = "Hello, World!";
	const std::size_t size = sizeof("Hello, World!");

	SomeBadClass badClass;

	badClass.initialize_length(size);
	badClass.initialize_pointer(str);
	badClass.initialize_initialized();

	auto value = badClass.getString();
	std::cout << value << std::endl;
}



int main() {
	correctUsage();

	SomeBadClass badClass;

	// 1 - wrong usage before initialization
	try {
		badClass.getString();
	}
	catch(const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	const char * str = "Hello, World!";

	// 3 - usage after the partial initialization
	try {
		badClass.initialize_pointer(str);
		badClass.getString();
	}
	catch(const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	const std::size_t size = sizeof("Hello, World!");

	// 2 - usage after the partial initialization
	try {
		badClass.initialize_length(size);
		badClass.getString();
	}
	catch(const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	// 4 - usage after the full initialization
	try {
		badClass.initialize_initialized();
		auto value = badClass.getString();
		std::cout << value << std::endl;
	}
	catch(const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	return 0;
}