#include <iostream>
#include <memory>

struct SomeStruct : std::enable_shared_from_this<SomeStruct> {
    SomeStruct() {
        std::cout << "ctor" << std::endl;
    }
    ~SomeStruct() {
        std::cout << "dtor" << std::endl;
    }

    std::shared_ptr<SomeStruct> getPtr() {
        return shared_from_this();
    }
};

int main() {
    {
        auto ptr1 = std::shared_ptr<SomeStruct>{new SomeStruct{}};
        auto ptr2 = ptr1->getPtr();
        std::cout << "before scope end" << std::endl;
    }
    std::cout << "after scope" << std::endl;

    return 0;
}