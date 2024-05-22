// Exercise: For convergent_point to work, it must be called with elements whose
// distances to the convergent point are equal. Implement an algorithm
// convergent_point_guarded for use when that is not known to the case, but
// there is an element in common to the oribts of both.

// I'm not sure about this one.
// convergent_point should work anyway if one of the elements is in a cycle, at
// the convergent point n away and the other is in a handle 2n away.

#include "collision_point.hpp"
#include "modulo_cycles.hpp"

#include <iostream>

int main() {
  OrbitModuloTenOperation operation;
  std::cout << std::boolalpha;
  // true, these orbits intersect. (2 will reach 3 in one hop)
  std::cout << do_intersect(operation, 2, 3) << std::endl;
  OrbitModuloTenOperationBrokenNonCircular broken_op;
  // true, both will fall into the "5" hole
  std::cout << do_intersect(broken_op, 2, 4) << std::endl;
  OrbitZeroThroughThreeElseTerminate terminate_gt_three_op;
  // should not intersect. 2 will orbit [0, 2], 5 will terminate at -1
  // immediately
  std::cout << do_intersect(terminate_gt_three_op, 2, 5) << std::endl;
}