#include <iostream>
#include <numeric>
#include <vector>



void test_accumulate() {
    std::vector<int> values = {3, 5, 1, 2, 3, 6, 7, 8, 9, 9, 9, 9, 5, 4, 3, 0};

    // T accumulate( InputIt first, InputIt last, T init,
    //           BinaryOperation op )

    std::cout << "result = " << 
        std::accumulate(values.cbegin(), values.cend(),
        0,
        [](int sum, int v) {
            return sum + v;
        });
    
}

int main() {

    test_accumulate();

    return 0;
}