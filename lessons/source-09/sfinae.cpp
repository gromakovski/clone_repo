#include <iostream>
#include <string>
#include <type_traits>

struct SomeStruct {

	template<typename TT, 
		typename Fake = 
			typename std::enable_if<
				!std::is_same<typename std::remove_reference<TT>::type, 
					SomeStruct>::value, void>::type
	>
	SomeStruct(TT&& value) : m_value{std::forward<TT>(value)} {

	}

	SomeStruct(const SomeStruct& other) : m_value{other.m_value} {

	}

    const std::string& getValue() const {
		return m_value;
	}

private:
	std::string m_value;
	std::string m_value2;
};


void printIt(const std::string& value) {
	std::cout << "ref/value: " << value << std::endl;
}

void printIt(std::string&& value) {
	std::cout << "r-value: " << value << std::endl; 
}

template<typename T>
void templateFunction(T&& someValue) {
	printIt(someValue);
}

template<typename T>
void templateFunction2(T&& someValue) {
	printIt(std::forward<T>(someValue));
}

int main() {

	std::string value{"Hello, world!"};
	std::cout << "printIt test:\n";
	printIt(value);
	printIt(std::move(value));
	printIt(std::string("Temporary"));

	std::cout << "\ntemplateFunction test:\n";
	templateFunction(value);
	templateFunction(std::move(value));
	templateFunction(std::string("Temporary"));

	std::cout << "\ntemplateFunction2 test:\n";
	templateFunction2(value);
	templateFunction2(std::move(value));
	templateFunction2(std::string("Temporary"));



	SomeStruct first("Hello, World!");
	SomeStruct second = first;

	return 0;
}
