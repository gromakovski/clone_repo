#include <iostream>
#include <thread>

#include <cstdlib>
#include <cstring>

struct MyString {
    MyString() : m_buffer{nullptr}, m_size{0} {

    }

    ~MyString() {
        delete [] m_buffer;
    }

    void assign(const char * str) {
        m_size = std::strlen(str);
        delete [] m_buffer;

        m_buffer = new char[m_size];

        memcpy(m_buffer, str, m_size);
    }

    friend
    std::ostream& operator<<(std::ostream& os, const MyString& str) {
        os << str.m_buffer << std::endl;
        return os;
    }

private:
    char * m_buffer;
    std::size_t m_size;
};

int main() {
    MyString string;

    string.assign("Hello, World!");

    std::cout << string << std::endl;

    return 0;
}