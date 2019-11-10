#include <cstring>
#include <iostream>
#include <string>

int main() {

    std::string value = "Hello, world!";
    
    // Ask data and make operation
    auto len = std::strlen(value.data());
    auto pos = std::strstr(value.data(), "world!");

    // Tell, what to do
    auto len2 = value.size();
    auto pos2 = value.find("world!");

    return 0;
}