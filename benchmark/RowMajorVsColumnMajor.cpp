#include <benchmark/benchmark.h>
#include <tcc/Matrix.h>
#include <tcc/MatrixUtils.h>
#include <fmt/format.h>

static size_t BM_SetupState(benchmark::State &state)
{
  const auto size = state.range(0);
  const auto sizeInBytes = size * size * sizeof(Matrix::ValueType);

  state.SetComplexityN(size);
  state.SetLabel(fmt::format("{} Kb ({}x{} matrix)", sizeInBytes / 1024, size, size));

  return static_cast<size_t>(size);
}

static void BM_ColumnMajor_sumElements(benchmark::State &state)
{
  auto size = BM_SetupState(state);
  auto matrix = Matrix{ size, size };
  fillRandom(matrix, .0F, 1.0F);

  for (auto _ : state) {
    benchmark::ClobberMemory();
    auto total = Matrix::ValueType{};
    for (size_t col = 0; col < matrix.cols(); col++) {
      for (size_t row = 0; row < matrix.rows(); row++) {
        benchmark::DoNotOptimize(total += matrix.at(row, col));
      }
    }
    benchmark::DoNotOptimize(total);
  }

  state.SetBytesProcessed(matrix.size() * sizeof(Matrix::ValueType) * state.iterations());
  state.SetItemsProcessed(matrix.size() * state.iterations());
}

static void BM_RowMajor_sumElements(benchmark::State &state)
{
  auto size = BM_SetupState(state);

  auto matrix = Matrix{ size, size };
  fillRandom(matrix, .0F, 1.0F);

  for (auto _ : state) {
    benchmark::ClobberMemory();
    auto total = Matrix::ValueType{};
    for (size_t row = 0; row < matrix.rows(); row++) {
      for (size_t col = 0; col < matrix.cols(); col++) {
        benchmark::DoNotOptimize(total += matrix.at(row, col));
      }
    }
    benchmark::DoNotOptimize(total);
  }

  state.SetBytesProcessed(matrix.size() * sizeof(Matrix::ValueType) * state.iterations());
  state.SetItemsProcessed(matrix.size() * state.iterations());
}

constexpr auto testMin = 1 << 4;
constexpr auto testStep = 1 << 6;
constexpr auto testMax = testMin + 32 * testStep;

BENCHMARK(BM_ColumnMajor_sumElements)
  ->Complexity(benchmark::BigO::oNSquared)
  ->Unit(benchmark::kMillisecond)
  ->DenseRange(testMin, testMax, testStep);

BENCHMARK(BM_RowMajor_sumElements)
  ->Complexity(benchmark::BigO::oNSquared)
  ->Unit(benchmark::kMillisecond)
  ->DenseRange(testMin, testMax, testStep);