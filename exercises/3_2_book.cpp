#include "powers.hpp"

#include <iostream>

int main() {
  size_t n = 3;
  int a = 1;
  std::cout << power_left_associated(a, n, std::minus<>()) << std::endl;

  std::cout << power_right_associated(a, n, std::minus<>()) << std::endl;

  std::cout << power_0(3, 8, std::multiplies<>()) << std::endl;
}