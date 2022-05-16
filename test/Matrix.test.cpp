#include "tcc/MatrixUtils.h"
#include <gtest/gtest.h>
#include <tcc/Matrix.h>

TEST(Matrix, ZeroInit)
{
  constexpr size_t matrixSize = 10;
  auto matrix = Matrix{ matrixSize };
  EXPECT_EQ(matrix.rows(), matrixSize);
  EXPECT_EQ(matrix.cols(), matrixSize);
  EXPECT_EQ(std::distance(matrix.begin(), matrix.end()), matrixSize * matrixSize);
}

TEST(Matrix, Fill)
{
  constexpr size_t matrixSize = 10;
  constexpr uint32_t someValue = 12;
  auto matrix = Matrix{ matrixSize };
  fill(matrix, someValue);

  EXPECT_EQ(matrix.at(0, 0), someValue);
  EXPECT_EQ(matrix.at(3, 3), someValue);
  EXPECT_EQ(matrix.at(9, 9), someValue);
  ASSERT_ANY_THROW(matrix.at(10, 10));
  ASSERT_ANY_THROW(matrix.at(11, 11));
}

TEST(Matrix, RandomFill)
{
  constexpr size_t matrixSize = 10;
  constexpr uint32_t minRange = 1;
  constexpr uint32_t maxRange = 12;
  auto matrix = Matrix{ matrixSize };
  fillRandom(matrix, minRange, maxRange);

  EXPECT_NE(matrix.at(0, 0), 0);
}

TEST(Matrix, SetValue)
{
  constexpr size_t matrixSize = 10;
  constexpr uint32_t someValue = 12;
  auto matrix = Matrix{ matrixSize };
  fill(matrix, someValue);

  matrix.at(2, 3) = 5;

  EXPECT_EQ(matrix.at(2, 3), 5);
  EXPECT_NE(matrix.at(3, 2), 5);
  EXPECT_EQ(matrix.at(3, 3), someValue);
  EXPECT_EQ(matrix.at(9, 9), someValue);
  ASSERT_ANY_THROW(matrix.at(10, 10));
  ASSERT_ANY_THROW(matrix.at(11, 11));
}