#include <benchmark/benchmark.h>
#include <tcc/Matrix.h>
#include <tcc/MatrixUtils.h>

Matrix::ValueType ColumnMajor_sumElements(const Matrix &matrix)
{
  auto total = .0f;
  for (size_t col = 0; col < matrix.cols(); col++) {
    for (size_t row = 0; row < matrix.rows(); row++) {
      benchmark::DoNotOptimize(total += matrix.at(row, col));
    }
  }

  return total;
}

Matrix::ValueType RowMajor_sumElements(const Matrix &matrix)
{
  auto total = .0f;
  for (size_t row = 0; row < matrix.rows(); row++) {
    for (size_t col = 0; col < matrix.cols(); col++) {
      benchmark::DoNotOptimize(total += matrix.at(row, col));
    }
  }

  return total;
}

static void BM_ColumnMajor_sumElements(benchmark::State &state)
{
  const auto size = state.range(0);
  state.SetComplexityN(size);

  auto matrix = Matrix{ static_cast<size_t>(size) };
  fillRandom(matrix, .0F, 1.0F);

  for (auto _ : state) { ColumnMajor_sumElements(matrix); }
}

constexpr auto testScale = 1'000;
constexpr auto testStep = testScale / 10;
constexpr auto testLimit = testScale * 8;

BENCHMARK(BM_ColumnMajor_sumElements)
  ->DenseRange(0, testLimit, testStep)
  ->Complexity(benchmark::oNSquared);

static void BM_RowMajor_sumElements(benchmark::State &state)
{
  const auto size = state.range(0);
  state.SetComplexityN(size);

  auto matrix = Matrix{ static_cast<size_t>(size) };
  fillRandom(matrix, .0F, 1.0F);

  for (auto _ : state) { RowMajor_sumElements(matrix); }
}

BENCHMARK(BM_RowMajor_sumElements)
  ->DenseRange(0, testLimit, testStep)
  ->Complexity(benchmark::oNSquared);