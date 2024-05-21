// Exercise: Design an algorithm that determines, given a transformation and its
// definition-space predicate, whether the orbits of two elements intersect

#include <concepts>
#include <functional>
#include <iostream>
#include <numeric>
#include <type_traits>

#include "OutOfDefinitionSpace.hpp"

using DistanceType = int;

template <typename function_t, typename type_p>
concept is_homogeneous_unary_function = requires(function_t f, type_p a) {
  { std::invoke(f, a) } -> std::same_as<type_p>;
};

template <typename Function, typename Type>
concept is_predicate_function = requires(Function f, Type a) {
  { std::invoke(f, a) } -> std::convertible_to<bool>;
};

template <typename Struct, typename Type>
concept Transformation = requires(Struct s, Type t) {
  { s.func } -> is_homogeneous_unary_function<Type>;
  { s.pred } -> is_predicate_function<Type>;
  { s(t) } -> std::convertible_to<Type>;
};

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

template <typename F, typename P>
  requires Transformation<F, P>
P apply_transformation(F transformation, P param) {
  return transformation(param);
}

int main() {
  OrbitModuloTenOperation operation;
  std::cout << apply_transformation(operation, 2) << std::endl;
}