
#include <math.h>
#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
  int n, k;
  std::cin >> n >> k;

  int res;

  // res = 2 * (n / k) + (n % k != 0) + ((n % k > k / 2.0) || (n < k));

  if (n % k == 0) {
    res = 2 * n / k;
  }

  if (n % k > k / 2) {
    res = 2 * ceil(n / k);
  }
  if (n % k <= k / 2) {
    res = 2 * (n / k);
  }

  if (n < k) {
    res = 2;
  }

  std::cout << res;

  // std::cout << n * (m + 1);

  return 0;
}
