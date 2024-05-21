#pragma once

#include <stdexcept>

struct OutOfDefinitionSpace : public std::runtime_error {
  OutOfDefinitionSpace(const std::string &what = "")
      : std::runtime_error(what) {}
};
