#pragma once

#include <vector>

template<typename T>
struct Matrix
{
  std::vector<T> mData;
  size_t numColumns{};

  constexpr explicit Matrix(size_t size) : Matrix{ size, size } {}

  constexpr Matrix(size_t numRows, size_t numColumns) : mData{}, numColumns{ numColumns }
  {
    mData.resize(numRows * numColumns);
  }

  const T &at(size_t row, size_t column) const { return mData.at(column + numColumns * row); }

  T &at(size_t row, size_t column) { return mData.at(column + numColumns * row); }

  auto begin() const { return mData.begin(); }

  auto end() const { return mData.end(); }

  auto begin() { return mData.begin(); }

  auto end() { return mData.end(); }

  auto data() const { return mData.data(); }

  [[nodiscard]] size_t rows() const { return mData.size() / numColumns; }
  [[nodiscard]] size_t cols() const { return numColumns; }
};
