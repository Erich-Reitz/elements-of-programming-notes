#pragma once

#include <cassert>

#include "m_named_traits.hpp"

/** The collision point of a transformation f and a starting point x is the
 * unique y such that y = f^n(x) = f^(2n + 1)(x)*/
template <typename F, typename E>
  requires Transformation<F, E>
auto collision_point(const F &f, E x) -> E {
  if (!f.pred(x)) {
    return x;
  }

  E slow = x;
  E fast = f(x);
  while (slow != fast) {
    slow = f(slow);
    if (!f.pred(fast))
      return fast;
    fast = f(fast);
    if (!f.pred(fast))
      return fast;
    fast = f(fast);
  }
  return fast;
}

/** Specialization of collision_point for elements known to be non-terminating*/
template <typename F, typename E>
  requires Transformation<F, E>
auto collision_point_nonterminating_orbit(const F &f, E x) -> E {
  E slow = x;
  E fast = f(x);
  while (slow != fast) {
    slow = f(slow);
    fast = f(fast);
    fast = f(fast);
  }
  return fast;
}

/** Procedure to determine whether an orbit is terminating*/
template <typename F, typename E>
  requires Transformation<F, E>
auto terminating(const F &f, E x) -> bool {
  return !f.pred(collision_point(f, x));
}

template <typename F, typename E>
  requires Transformation<F, E>
auto circular(const F &f, const E &x) -> bool {
  return x == f(collision_point_nonterminating_orbit(f, x));
}

template <typename F, typename E>
  requires Transformation<F, E>
auto circular_nonterminating_orbit(const F &f, const E &x) -> bool {
  const auto p_x_defined = f.pred(x);
  assert(p_x_defined);
  E y = collision_point(f, x);
  return f.pred(y) && x == f(y);
}