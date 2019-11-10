// Format

#include <boost/format.hpp>
#include <iostream>
#include <string>

struct Animal {
    std::string name;
    int legs;
};

std::ostream &operator<<(std::ostream &os, const Animal &a) {
    return os << a.name << ',' << a.legs;
}

int main() {
    std::cout << boost::format{"%1% [%2%] %3%"} % "2018-01-12" % "info" % 
            (boost::format{"%1% was open"} % "test.txt") << std::endl;

    try {
        std::cout << boost::format{"%d %d %d"} % 1 % 2 % 3 % 4 << std::endl;
    }
    catch(const std::exception& ex) {
        std::cout << "failed! " << ex.what() << std::endl;
    }

    try {
        std::cout << boost::format{"%d %d %d"} % 1 % 2 << std::endl;
    }
    catch(const std::exception& ex) {
        std::cout << "failed! " << ex.what() << std::endl;
    }

    std::cout << "with int as string:" << std::endl;
    std::cout << boost::format{"%s"} % 42 << std::endl;

    Animal animal{"Lucky", 4};
    std::cout << boost::format("%1%") % animal << std::endl;

    return 0;
}
