#pragma once

#include "m_named_traits.hpp"

// todo: fix this
using DistanceType = long long;

template <typename F, typename E>
  requires Transformation<F, E>
auto distance(const F &f, E x, E y) -> DistanceType {
  using N = DistanceType;
  N n(0);
  while (x != y) {
    x = f(x);
    n = n + N(1);
  }

  return n;
}