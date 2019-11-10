// Circular Buffer

#include <iostream>
#include <string>

#include <boost/circular_buffer.hpp>

int main() {
    boost::circular_buffer<int> buffer{10};

    for(int i = 0; i < 1024; ++i)
    {
        buffer.push_back(i);
    }

    for (auto& i : buffer) {
        std::cout << i << std::endl;
    }

    return 0;
}
