// Exercise: Design an algorithm that determines, given a transformation and its
// definition-space predicate, whether the orbits of two elements intersect

#include "OutOfDefinitionSpace.hpp"
#include "m_named_traits.hpp"

#include <iostream>

struct OrbitModuloTenOperation {
  std::function<int(int)> func = [](int n) -> int {
    n = n + 1;
    return n % 10;
  };

  std::function<bool(int)> pred = [](int n) -> bool {
    return (0 <= n) && (n <= 9);
  };

  int operator()(int x) { return apply(x); }

private:
  int apply(int n) {
    if (!pred(n)) {
      throw OutOfDefinitionSpace("!pred(n) OrbitModuloTenOperation");
    }

    return func(n);
  }
};

int main() {
  OrbitModuloTenOperation operation;
  std::cout << apply_transformation(operation, 2) << std::endl;
}