#include "tcc/MatrixUtils.h"
#include <benchmark/benchmark.h>
#include <tcc/Matrix.h>

size_t ColumnMajor_countNonZeroElements(const Matrix<uint32_t> &matrix)
{
  size_t total = 0;
  for (auto col = 0; col < matrix.cols(); col++) {
    for (auto row = 0; row < matrix.rows(); row++) {
      if (matrix.at(row, col) != 0) benchmark::DoNotOptimize(total++);
    }
  }

  return total;
}

size_t RowMajor_countNonZeroElements(const Matrix<uint32_t> &matrix)
{
  size_t total = 0;
  for (auto row = 0; row < matrix.rows(); row++) {
    for (auto col = 0; col < matrix.cols(); col++) {
      if (matrix.at(row, col) != 0) { benchmark::DoNotOptimize(total++); }
    }
  }

  return total;
}

static void BM_ColumnMajor_countNonZeroElements(benchmark::State &state)
{
  auto matrix = Matrix<uint32_t>{ static_cast<size_t>(state.range(0)) };
  fillRandom<uint32_t>(matrix, 0, 3);

  for (auto _ : state) { benchmark::DoNotOptimize(ColumnMajor_countNonZeroElements(matrix)); }
}
BENCHMARK(BM_ColumnMajor_countNonZeroElements)->RangeMultiplier(2)->Range(8, 8 << 10);

static void BM_RowMajor_countNonZeroElements(benchmark::State &state)
{
  auto matrix = Matrix<uint32_t>{ static_cast<size_t>(state.range(0)) };
  fillRandom<uint32_t>(matrix, 0, 3);

  for (auto _ : state) { benchmark::DoNotOptimize(RowMajor_countNonZeroElements(matrix)); }
}
BENCHMARK(BM_RowMajor_countNonZeroElements)->RangeMultiplier(2)->Range(8, 8 << 10);