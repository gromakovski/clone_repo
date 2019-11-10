#include <array>
#include <iostream>
#include <vector>

using IPV4_t = std::array<short, 4>;

#pragma region(Solution)
std::ostream& operator<<(std::ostream& os, const IPV4_t& ip) {
    os << ip[0] << '.'
       << ip[1] << '.'
       << ip[2] << '.'
       << ip[3] << std::endl;
    return os;
}
#pragma endregion

#pragma region(Other)
// struct IPV4_t {
//     short first;
//     short second;
//     short third;s
//     short fourth;
// };
#pragma endregion

struct IPPool {
    void append(const IPV4_t& ip) {
        m_pool.push_back(ip);
    }

    void printAll() {
        for (const auto& ip : m_pool) {
            std::cout << ip[0] << '.'
                << ip[1] << '.'
                << ip[2] << '.'
                << ip[3] << std::endl;
        }
    }

private:
    std::vector<IPV4_t> m_pool;
};


int main() {

    IPPool pool;
    pool.append({127, 0, 0, 1});
    pool.append({127, 0, 0, 2});

    pool.printAll();


    std::vector<int> values = {0, 1, 2, 3, 4, 5};
    std::cout << "values[3] = " << *(values.data() + 3) << std::endl;

    return 0;
}