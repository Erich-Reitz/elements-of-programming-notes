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

struct OrbitZeroThroughThreeElseTerminate {
  std::function<int(int)> func = [](int n) -> int {
    if (0 <= n && n <= 2) {
      return (++n % 3); 
    }
    return -1; 
  };

  std::function<bool(int)> pred = [](int n) -> bool {
    return (0 <= n) && (n <= 2);
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
  // true, these orbits intersect. (2 will reach 3 in one hop)
  std::cout << do_intersect(operation, 2, 3) << std::endl;
  OrbitModuloTenOperationBrokenNonCircular broken_op; 
  // true, both will fall into the "5" hole
  std::cout << do_intersect(broken_op, 2, 4) << std::endl;
  OrbitZeroThroughThreeElseTerminate terminate_gt_three_op; 
  // should not intersect. 2 will orbit [0, 2], 5 will terminate at -1 immediately
  std::cout << do_intersect(terminate_gt_three_op, 2, 5) << std::endl;
}