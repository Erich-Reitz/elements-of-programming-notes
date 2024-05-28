#pragma once

#include <concepts>
#include <functional>
#include <type_traits>

template <typename function_t, typename type_p>
concept is_homogeneous_unary_function = requires(function_t f, type_p a) {
  { std::invoke(f, a) } -> std::same_as<type_p>;
};

template <typename function_t, typename type_p>
concept is_homogeneous_binary_function =
    requires(function_t f, type_p a, type_p b) {
      { std::invoke(f, a, b) } -> std::same_as<type_p>;
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