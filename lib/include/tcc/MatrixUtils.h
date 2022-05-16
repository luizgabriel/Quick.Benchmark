#pragma once

#include "Matrix.h"
#include <algorithm>
#include <limits>
#include <random>

void fill(Matrix &matrix, Matrix::ValueType value) { std::fill(matrix.begin(), matrix.end(), value); }

void fillRandom(Matrix &matrix,
  Matrix::ValueType min = std::numeric_limits<Matrix::ValueType>::min(),
  Matrix::ValueType max = std::numeric_limits<Matrix::ValueType>::max())
{
  auto randomDevice = std::random_device{};
  auto generator = std::mt19937{ randomDevice() };
  auto distrib = std::uniform_real_distribution<Matrix::ValueType>(min, max);
  std::generate(matrix.begin(), matrix.end(), [&]() { return distrib(generator); });
}