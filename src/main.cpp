#include <benchmark/benchmark.h>

static void StringCreation(benchmark::State& state) {
  for (auto _ : state) {
    std::string created_string("hello");
    benchmark::DoNotOptimize(created_string);
  }
}

BENCHMARK(StringCreation);

static void StringCopy(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state) {
    std::string copy(x);
  }
}

BENCHMARK(StringCopy);