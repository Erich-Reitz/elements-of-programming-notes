
#include "OutOfDefinitionSpace.hpp"

#include <functional>

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
    if (n == 5)
      return -1;
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
