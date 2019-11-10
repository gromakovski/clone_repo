
#include <iostream>

int main(int argc, char const *argv[]) {
  int a, b;
  std::cin >> a >> b;
  int *aOrb = nullptr;

  for (int i = 0; i <= 9999; i++) {
    if (i % 2 == 0)
      aOrb = &a;
    else
      aOrb = &b;

    if (*aOrb == i) {
      std::cout << "yes";
      return 0;
    }
  }

  std::cout << "no";

  return 0;
}

// cool answer from timus
//#include <iostream>
// using namespace std;

// int main() {
//    int lock1, lock2;
//    cin >>lock1 >>lock2;

//    if (lock1 % 2 == 0 || lock2 % 2 != 0)
//        cout << "yes" << endl;
//    else
//        cout << "no" << endl;
//    return 0;
//}
