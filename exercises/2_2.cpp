// Exercise: Design an algorithm that determines, given a transformation and its
// definition-space predicate, whether the orbits of two elements intersect

#include "OutOfDefinitionSpace.hpp"
#include "collision_point.hpp"
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

  auto operator()(int x) const -> int { return apply(x); }

private:
  auto apply(int n) const -> int {
    if (!pred(n)) {
      throw OutOfDefinitionSpace("!pred(n) OrbitModuloTenOperation");
    }

    return func(n);
  }
};


struct OrbitModuloTenOperationBrokenNonCircular {
  std::function<int(int)> func = [](int n) -> int {
    if (n == 5) return -1 ;
    n = n + 1;
    return n % 10;
  };

  std::function<bool(int)> pred = [](int n) -> bool {
    return (0 <= n) && (n <= 9);
  };

  auto operator()(int x) const -> int { return apply(x); }

private:
  auto apply(int n) const -> int {
    if (!pred(n)) {
      throw OutOfDefinitionSpace("!pred(n) OrbitModuloTenOperation");
    }

    return func(n);
  }
};

int main() {
  OrbitModuloTenOperation operation;
  std::cout << std::boolalpha; 
  std::cout << circular(operation, 2) << std::endl;
  OrbitModuloTenOperationBrokenNonCircular broken_op; 
  std::cout << circular(broken_op, 2) << std::endl;
}