#pragma once

#include "m_named_traits.hpp"

#include <type_traits>

template <typename I, typename Op, typename Domain = std::invoke_result<Op>>
  requires(std::is_integral_v<I> && is_homogeneous_binary_function<Op, Domain>)
Domain power_0(Domain a, I n, Op op) {
  if (n == I(1)) {
    return a;
  }

  const auto sqd = op(a, a);
  if (n % I(2) == I(0)) {
    return power_0(sqd, n / I(2), op);
  }

  return op(power_0(sqd, n / I(2), op), a);
}

// point: reduce the code size of power_0 by consolidating the two recursive calls
template <typename I, typename Op, typename Domain = std::invoke_result<Op>>
  requires(std::is_integral_v<I> && is_homogeneous_binary_function<Op, Domain>)
Domain power_1(Domain a, I n, Op op) {
  if (n == I(1)) {
    return a;
  }

  Domain result = power_1(op(a, a), n / I(2), op);
  if (n % I(2) == I(1)) {
    result = op(result, a);
  }
  return result;
}


template <typename I, typename Op, typename Domain = std::invoke_result<Op>>
  requires(std::is_integral_v<I> && is_homogeneous_binary_function<Op, Domain>)
Domain power_left_associated(Domain a, I n, Op op) {
  if (n == I(1)) {
    return a;
  }

  return op(power_left_associated(a, n - I(1), op), a);
}

template <typename I, typename Op, typename Domain = std::invoke_result<Op>>
  requires(std::is_integral_v<I> && is_homogeneous_binary_function<Op, Domain>)
Domain power_right_associated(Domain a, I n, Op op) {
  if (n == I(1)) {
    return a;
  }

  return op(a, power_left_associated(a, n - I(1), op));
}
