// Exercise: Implement a definition-space predicate for addition on 32 bit
// signed integers

#include <iostream>
#include <numeric>
#include <stdexcept>

struct OutOfDefinitionSpace : public std::runtime_error {
  OutOfDefinitionSpace(const std::string &what = "")
      : std::runtime_error(what) {}
};

int add(int n1, int n2) {
  auto within_definition_space = [](int a, int b) -> bool {
    const auto max_int = std::numeric_limits<int>::max();
    const auto min_int = std::numeric_limits<int>::min();
    // sum of (a, b) > max_int => can only happen if both are positive (> 0)
    // sum of (a, b) < min_int => can only happen if both are negative (< 0)
    if (a > 0) {
      // move the bar down, and make sure b is less (because b will bring it up)
      return b <= max_int - a;
    }

    if (a < 0) {
      // move the bar up, and make sure b is greater (because b will lower it)
      return b >= min_int - a;
    }

    return true;
  };
  if (!within_definition_space(n1, n2)) {
    throw OutOfDefinitionSpace("Will Overflow");
  }

  return n1 + n2;
}

int main() {
  // should = int max
  std::cout << add(1, std::numeric_limits<int>::max() - 1) << std::endl;
  std::cout << add(0, std::numeric_limits<int>::max()) << std::endl;
  // symmetry
  std::cout << add(std::numeric_limits<int>::max() - 1, 1) << std::endl;
  std::cout << add(std::numeric_limits<int>::max(), 0) << std::endl;
  // should overflow
  // std::cout << add(1, std::numeric_limits<int>::max() ) << std::endl;
  // std::cout << add(std::numeric_limits<int>::max(), 1 ) << std::endl;

  // should equal int min
  std::cout << add(0, std::numeric_limits<int>::min()) << std::endl;
  std::cout << add(-1, std::numeric_limits<int>::min() + 1) << std::endl;

  std::cout << add(std::numeric_limits<int>::min(), 0) << std::endl;
  std::cout << add(std::numeric_limits<int>::min() + 1, -1) << std::endl;

  // should overflow
  // std::cout << add(-1, std::numeric_limits<int>::min() ) << std::endl;
  // std::cout << add(std::numeric_limits<int>::min(), -1 ) << std::endl;
}