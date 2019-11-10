
#include <math.h>
#include <array>
#include <cassert>
#include <iostream>
#include <vector>
// 4 3 2 5 7  5 3 11 17

constexpr bool isPrime(unsigned long number) {
  for (unsigned long d = 2; d <= sqrt(number); d++) {
    if (number % d == 0) return false;
  }
  return true;
}
const int PRIMESCOUNT = 15000;
std::array<unsigned long, PRIMESCOUNT> generatePrimes() {
  std::array<unsigned long, PRIMESCOUNT> primes{0};
  int countPrimes = 0;
  unsigned long current = 2;
  while (countPrimes != PRIMESCOUNT) {
    if (isPrime(current)) {
      primes[countPrimes] = current;
      countPrimes++;
    }
    current++;
  }

  return primes;
}
std::array<unsigned long, PRIMESCOUNT> primes = generatePrimes();

int main(int argc, char const *argv[]) {
  // isPrime(3);
  // isPrime(4);
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    int number;
    std::cin >> number;
    std::cout << primes[number - 1] << std::endl;
  }

  return 0;
}
