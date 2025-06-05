#include <benchmark/benchmark.h>
#include <iostream>
#include <cstdint>

static std::int64_t factorial(std::int64_t n) {
  if (n < 0) {
    return 0;
  } else if (n == 0) {
    return 1;
  } else {
    return n * factorial(n - 1);
  }
}
static void BM_1(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(factorial(20));
  }
}
BENCHMARK(BM_1);

static std::int64_t factorial_tail(std::int64_t n, std::int64_t val) {
  if (n < 0) {
    return 0;
  } else if (n == 0) {
    return 1;
  } else if (n == 1) {
    return val;
  } else {
    return factorial_tail(n - 1, n * val);
  }
}
static void BM_2(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(factorial_tail(20, 1));
  }
}
BENCHMARK(BM_2);

BENCHMARK_MAIN();
