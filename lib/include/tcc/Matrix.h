#pragma once

#include <vector>

struct Matrix
{
public:
  using ValueType = float;

  [[nodiscard]] const auto &at(size_t rowIndex, size_t colIndex) const
  {
    return mData.at((mRows * rowIndex) + colIndex);
  }

  auto &at(size_t rowIndex, size_t colIndex) { return mData.at((mRows * rowIndex) + colIndex); }

  [[nodiscard]] auto begin() const { return mData.begin(); }

  [[nodiscard]] auto end() const { return mData.end(); }

  auto begin() { return mData.begin(); }

  auto end() { return mData.end(); }

  [[nodiscard]] size_t rows() const { return mRows; }
  [[nodiscard]] size_t cols() const { return mCols; }

  explicit Matrix(size_t size) : mRows{ size }, mCols{ size } { mData.resize(mRows * mCols); }

private:
  size_t mRows;
  size_t mCols;
  std::vector<ValueType> mData;
};
