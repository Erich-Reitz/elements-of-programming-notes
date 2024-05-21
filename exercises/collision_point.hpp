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

template <typename F, typename E>
  requires Transformation<F, E>
auto convergent_point(const F &f, E x0, E x1) -> E {
  while (x0 != x1) {
    x0 = f(x0);
    x1 = f(x1);
  }

  return x0;
}

template <typename F, typename E>
  requires Transformation<F, E>
auto connection_point_nonterminating_orbit(const F &f, E x) -> E {
  return convergent_point(f, x, f(collision_point_nonterminating_orbit(x, f)));
}

template <typename F, typename E>
  requires Transformation<F, E>
auto connection_point(const F &f, E x) -> E {
  E y = collision_point(f, x);
  if (!f.pred(y))
    return y;

  return convergent_point(f, x, f(y));
}

template <typename F, typename E>
  requires Transformation<F, E>
auto do_intersect(const F &f, E x0, E x1) -> bool {
  E y0 = collision_point(f, x0);
  E y1 = collision_point(f, x1);
  // if they both reach some sink, then check to see if the sinks are equal to
  // eachother. if they aren't, then they never got on the same path
  if (!f.pred(y0) || !f.pred(y1)) {
    return y0 == y1;
  }
  // guard against y0 and y1 being in different cycles
  E ptr = y0;
  do {
    if (ptr == y1)
      return true;
    ptr = f(ptr);

  } while (ptr != y0);

  return false;
}