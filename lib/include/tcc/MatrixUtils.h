#pragma once

#include "Matrix.h"
#include <algorithm>
#include <limits>
#include <random>

template<typename T>
void fill(Matrix<T> &matrix, T value)
{
  std::fill(matrix.begin(), matrix.end(), value);
}

template<typename T>
void fillRandom(Matrix<T> &matrix, T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
{
  auto randomDevice = std::random_device{};
  auto generator = std::mt19937{ randomDevice() };
  auto distrib = std::uniform_int_distribution<T>(min, max);

  std::generate(matrix.begin(), matrix.end(), [&]() { return distrib(generator); });
}