#include <iostream>
#include <string>
#include <cassert>
#include <map>

void first() {
    int i = 0;
    i = i++ + i++;
    std::cout << i << std::endl;
}

void second() {
    std::string s = "but I have heard it works even if you don't believe in it";
    auto pos = s.find("even");
    s.replace(0, 4, "")
       .replace(pos, 4, "only")
       .replace(s.find(" don't"), 6, "");
    std::cout << s << std::endl;
    assert(s == "I have heard it works only if you believe in it");
}

void third() {
    std::map<int, size_t> dictionary;
    dictionary[0] = dictionary.size();
    std::cout << dictionary[0] << std::endl;
}

int main() {

    first();

    second();

    third();

    return 0;
}