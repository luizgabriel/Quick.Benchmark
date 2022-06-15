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

  auto &at(size_t rowIndex, size_t colIndex) { return mData.at((mSize * rowIndex) + colIndex); }

  [[nodiscard]] auto begin() const { return mData.begin(); }

  [[nodiscard]] auto end() const { return mData.end(); }

  auto begin() { return mData.begin(); }

  auto end() { return mData.end(); }

  [[nodiscard]] size_t rows() const { return mSize; }
  [[nodiscard]] size_t cols() const { return mSize; }

  explicit Matrix(size_t size) : mSize{ size } { mData.resize(mSize * mSize); }

  explicit Matrix(size_t size, ValueType value) : mSize{ size }
  {
    mData.resize(mSize * mSize);
    std::fill(mData.begin(), mData.end(), value);
  }

private:
  size_t mSize;
  std::vector<ValueType> mData;

  [[nodiscard]] size_t getInternalIndex(size_t rowIndex, size_t colIndex) const
  {
    return (mSize * rowIndex) + colIndex;
  }
};
