#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <string>


struct NoDefultCtor {
    NoDefultCtor() = delete;

    NoDefultCtor(const std::string& value) 
        : m_value{value} {
    }
private:
    std::string m_value;
};

void insert_or_assign() {
    using id_t = std::size_t;
    using name_t = std::string;

    std::map<id_t, name_t> clients;

    // 1. requires default constructor
    // 2. returns only T& - not iterator
    clients[20] = "Vasia";

    // 1. no default constructor need
    // 2. iterator as a result
    auto iter = clients.insert_or_assign(20, "Vasia");

    std::map<id_t, NoDefultCtor> values;
    // Compile error - no default constructor
    // values[10] = NoDefultCtor{"trololo"};
    auto iter2 = values.insert_or_assign(20, NoDefultCtor{"trololo"});
}


void try_emplace() {
    std::map<int, std::unique_ptr<std::string>> clients;

    auto ptr = std::make_unique<std::string>("Vasia");
    auto result1 = clients.emplace(20, std::move(ptr));
    assert(!ptr);

    auto ptr2 = std::make_unique<std::string>("Vasia");
    auto result2 = clients.emplace(20, std::move(ptr2));
    // assert(ptr2);
    // result2.first - iterator
    // result2.second - flag

    auto ptr3 = std::make_unique<std::string>("Vasia");
    auto result3 = clients.try_emplace(20, std::move(ptr3));
    assert(ptr3);
}



int main() {

    insert_or_assign();

    try_emplace();

    return 0;
}