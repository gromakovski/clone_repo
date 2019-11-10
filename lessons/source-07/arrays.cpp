#include <iostream>
#include <memory>

struct SomeStruct {
    SomeStruct() {
        std::cout << "ctor" << std::endl;
    }
    ~SomeStruct() {
        std::cout << "dtor" << std::endl;
    }
};

int main() {

    // undefined behavior
    //std::unique_ptr<SomeStruct> wrong{ new SomeStruct[10] };

    // Good
    std::unique_ptr<SomeStruct[]> ok{ new SomeStruct[10]};

    // std::shared_ptr<SomeStruct> wrong2{ new SomeStruct[10] };

    // Impossible in C++11/C++14
    std::shared_ptr<SomeStruct[]> ok2{ new SomeStruct[10] };

    return 0;
}