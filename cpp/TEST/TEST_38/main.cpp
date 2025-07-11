#include <type_traits>
#include <iostream>

using index_t = int;
template <index_t M, index_t N, typename S> struct mat {
  // matrix implementation
};

// Default dimensionality 0.
template <class T, typename = void>
struct dimensionality : std::integral_constant<index_t, 0> {};

template <typename S>
struct dimensionality<S, std::void_t<std::enable_if_t<std::is_arithmetic_v<S>>>> : std::integral_constant<index_t, 1024> {};

template <index_t M, index_t N, typename S>
struct dimensionality<mat<M, N, S>> : std::integral_constant<index_t, M * N> {};

template <class T>
inline constexpr index_t dimensionality_v = dimensionality<T>::value;

struct Foo {};

int main() {
  std::cout << dimensionality_v<double> << std::endl;
  std::cout << dimensionality_v<int> << std::endl;
  std::cout << dimensionality_v<float> << std::endl;
  std::cout << dimensionality_v<std::string> << std::endl;

  std::cout << dimensionality_v<mat<1, 2, double>> << std::endl;
  std::cout << dimensionality_v<mat<2, 2, float>> << std::endl;

  // static_assert(dimensionality_v<mat<1, 2, double>> == 2);
  // static_assert(dimensionality_v<mat<2, 2, float>> == 4);
  // static_assert(dimensionality_v<double> == 1);
  // static_assert(dimensionality_v<Foo> == 0);
  return 0;
}
