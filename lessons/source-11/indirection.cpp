#include <vector>

void just_a_value() {
    // We can work with value - cool!
    int value = 42;
    value += 2;
    value *= 4;
}

void pointer() {
    int array[] = {0, 1, 2, 3, 4, 5};

    int *ptr = &array[0];
    *ptr = 42;
    ptr += 3;
    *ptr = 24;
}

void vector() {
    std::vector<int> values = {0, 1, 2, 3, 4, 5, 6};
    values.size();
    values.push_back(42);
    values.front();
    values[3];
    values.clear();
}

int main() {


    return 0;
}