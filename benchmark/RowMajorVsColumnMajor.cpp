#include <tcc/MatrixUtils.h>
#include <benchmark/benchmark.h>
#include <tcc/Matrix.h>

size_t RowMajor_sumElements(const Matrix<uint32_t> &matrix)
{
  size_t sum = 0;
  for (auto col = 0; col < matrix.cols(); col++) {
    for (auto row = 0; row < matrix.rows(); row++) {
      benchmark::DoNotOptimize(sum += matrix.at(row, col));
    }
  }

  return sum;
}

size_t ColumnMajor_sumElements(const Matrix<uint32_t> &matrix)
{
  size_t sum = 0;
  for (auto row = 0; row < matrix.rows(); row++) {
    for (auto col = 0; col < matrix.cols(); col++) {
      benchmark::DoNotOptimize(sum += matrix.at(row, col));
    }
  }

  return sum;
}

static void BM_ColumnMajor_sumElements(benchmark::State &state)
{
  auto matrix = Matrix<uint32_t>{ static_cast<size_t>(state.range(0)) };
  fillRandom<uint32_t>(matrix, 0, 3);

  for (auto _ : state) { ColumnMajor_sumElements(matrix); }
}
BENCHMARK(BM_ColumnMajor_sumElements)->RangeMultiplier(2)->Range(8, 8 << 12);

static void BM_RowMajor_sumElements(benchmark::State &state)
{
  auto matrix = Matrix<uint32_t>{ static_cast<size_t>(state.range(0)) };
  fillRandom<uint32_t>(matrix, 0, 3);

  for (auto _ : state) { RowMajor_sumElements(matrix); }
}
BENCHMARK(BM_RowMajor_sumElements)->RangeMultiplier(2)->Range(8, 8 << 12);