#include <algorithm>
#include <array>
#include <chrono>
#include <thread>
#include <future>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <stack>
#include <list>

using Array      = std::vector<std::int32_t>;
using Solution_F = std::function<void(Array &)>;

template <class F>
struct y_combinator {
  F f; // the lambda will be stored here

  // a forwarding operator():
  template <class... Args>
  decltype(auto) operator()(Args &&...args) const {
    // we pass ourselves to f, then the arguments.
    return f(*this, std::forward<Args>(args)...);
  }
};

// helper function that deduces the type of the lambda:
template <class F>
y_combinator<std::decay_t<F>> make_y_combinator(F &&f) {
  return { std::forward<F>(f) };
}
