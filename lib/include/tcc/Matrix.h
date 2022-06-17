#pragma once

#include <vector>

struct Matrix
{
public:
  using ValueType = double;

  [[nodiscard]] const auto &at(size_t rowIndex, size_t colIndex) const
  {
    return mData.at(getInternalIndex(rowIndex, colIndex));
  }

  auto &at(size_t rowIndex, size_t colIndex)
  {
    return mData.at(getInternalIndex(rowIndex, colIndex));
  }

  [[nodiscard]] auto begin() const { return mData.begin(); }

  [[nodiscard]] auto end() const { return mData.end(); }

  auto begin() { return mData.begin(); }

  auto end() { return mData.end(); }

  [[nodiscard]] size_t rows() const { return mRows; }
  [[nodiscard]] size_t cols() const { return mCols; }
  [[nodiscard]] size_t size() const { return mRows * mCols; }

  explicit Matrix(size_t rows, size_t cols) : mRows{ rows }, mCols{cols} { mData.resize(size()); }

private:
  size_t mRows;
  size_t mCols;
  std::vector<ValueType> mData;

  [[nodiscard]] size_t getInternalIndex(size_t rowIndex, size_t colIndex) const
  {
    return (mCols * rowIndex) + colIndex;
  }
};
