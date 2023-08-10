#include <gtest/gtest.h>

#include <cmath>

#include "Matrix.hpp"

class NMMatrixTest : public ::testing::Test
{
};

TEST_F(NMMatrixTest, Creation)
{
    // Given
    NMMatrix matrix;

    // Then
    ASSERT_EQ(matrix.GetWidth(), 4);
    ASSERT_EQ(matrix.GetHeight(), 4);
}

TEST_F(NMMatrixTest, Creation_WithDimensions)
{
    // Given
    NMMatrix matrix(2, 3);

    // Then
    ASSERT_EQ(matrix.GetWidth(), 2);
    ASSERT_EQ(matrix.GetHeight(), 3);
}

TEST_F(NMMatrixTest, Creation_WithDimensionsAndDefaultValue)
{
    // Given
    NMMatrix matrix(2, 2, 1.0f);

    // Then
    ASSERT_EQ(matrix.GetWidth(), 2);
    ASSERT_EQ(matrix.GetHeight(), 2);
    ASSERT_EQ(matrix.Get(0, 0), 1.0f);
    ASSERT_EQ(matrix.Get(1, 0), 1.0f);
    ASSERT_EQ(matrix.Get(0, 1), 1.0f);
    ASSERT_EQ(matrix.Get(1, 1), 1.0f);
}

TEST_F(NMMatrixTest, Creation_WithDimensionsAndMultiDimensionalData)
{
    // Given
    std::vector<std::vector<float>> data = {{1.0f, 2.0f, 3.0f}, {4.0f, 5.0f, 6.0f}, {7.0f, 8.0f, 9.0f}};
    NMMatrix matrix(data);

    // Then
    ASSERT_EQ(matrix.GetWidth(), 3);
    ASSERT_EQ(matrix.GetHeight(), 3);
    ASSERT_EQ(matrix.Get(0, 0), 1.0f);
    ASSERT_EQ(matrix.Get(1, 0), 2.0f);
    ASSERT_EQ(matrix.Get(2, 0), 3.0f);
    ASSERT_EQ(matrix.Get(0, 1), 4.0f);
    ASSERT_EQ(matrix.Get(1, 1), 5.0f);
    ASSERT_EQ(matrix.Get(2, 1), 6.0f);
    ASSERT_EQ(matrix.Get(0, 2), 7.0f);
    ASSERT_EQ(matrix.Get(1, 2), 8.0f);
    ASSERT_EQ(matrix.Get(2, 2), 9.0f);
}

TEST_F(NMMatrixTest, Creation_WithDimensionsAndData)
{
    // Given
    std::vector<float> data = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
    NMMatrix matrix(2, 3, data);

    // Then
    ASSERT_EQ(matrix.GetWidth(), 2);
    ASSERT_EQ(matrix.GetHeight(), 3);
    ASSERT_EQ(matrix.Get(0, 0), 1.0f);
    ASSERT_EQ(matrix.Get(1, 0), 2.0f);
    ASSERT_EQ(matrix.Get(0, 1), 3.0f);
    ASSERT_EQ(matrix.Get(1, 1), 4.0f);
    ASSERT_EQ(matrix.Get(0, 2), 5.0f);
    ASSERT_EQ(matrix.Get(1, 2), 6.0f);
}

TEST_F(NMMatrixTest, OperatorEquality)
{
    // Given
    NMMatrix matrix1({
        {1.0f, 2.0f, 3.0f, 4.0f},
        {5.0f, 6.0f, 7.0f, 8.0f},
        {9.0f, 8.0f, 7.0f, 6.0f},
        {5.0f, 4.0f, 3.0f, 2.0f},
    });
    NMMatrix matrix2({
        {1.0f, 2.0f, 3.0f, 4.0f},
        {5.0f, 6.0f, 7.0f, 8.0f},
        {9.0f, 8.0f, 7.0f, 6.0f},
        {5.0f, 4.0f, 3.0f, 2.0f},
    });

    // Then
    ASSERT_TRUE(matrix1 == matrix2);
}

TEST_F(NMMatrixTest, OperatorEquality_NearEqual)
{
    // Given
    NMMatrix matrix1({
        {1.0f, 2.0f, 3.0f, 4.0f},
        {5.0f, 6.0f, 7.0f, 8.0f},
        {9.0f, 8.0f, 7.0f, 6.0f},
        {5.0f, 4.0f, 3.0f, 2.0f},
    });
    NMMatrix matrix2({
        {1.0f, 2.0f, 3.0f, 4.0f},
        {5.0f, 6.0f, 7.0f, 8.0f},
        {9.0f, 8.0f, 7.0f, 6.0f},
        {5.0f, 4.0f, 2.9999999f, 2.0000001f},
    });

    // Then
    ASSERT_TRUE(matrix1 == matrix2);
}

TEST_F(NMMatrixTest, OperatorEquality_NotEqual)
{
    // Given
    NMMatrix matrix1({
        {1.0f, 2.0f, 3.0f, 4.0f},
        {5.0f, 6.0f, 7.0f, 8.0f},
        {9.0f, 8.0f, 7.0f, 6.0f},
        {5.0f, 4.0f, 3.0f, 2.0f},
    });
    NMMatrix matrix2({
        {1.0f, 2.0f, 3.0f, 4.0f},
        {5.0f, 6.0f, 7.0f, 8.0f},
        {9.0f, 8.0f, 7.0f, 6.0f},
        {5.0f, 4.0f, 3.0f, 1.0f},
    });

    // Then
    ASSERT_FALSE(matrix1 == matrix2);
}

TEST_F(NMMatrixTest, StreamInsertionOperator)
{
    // Given
    NMMatrix matrix({
        {1.0f, 2.0f, 3.0f, 4.0f},
        {5.0f, 6.0f, 7.0f, 8.0f},
        {9.0f, 8.0f, 7.0f, 6.0f},
        {5.0f, 4.0f, 3.0f, 2.0f},
    });

    // When
    std::stringstream stream;
    stream << matrix;

    // Then
    ASSERT_EQ(stream.str(),
              "|  1.000  2.000  3.000  4.000 |\n"
              "|  5.000  6.000  7.000  8.000 |\n"
              "|  9.000  8.000  7.000  6.000 |\n"
              "|  5.000  4.000  3.000  2.000 |\n");
}

TEST_F(NMMatrixTest, StreamInsertionOperator_AutoExpand)
{
    // Given
    NMMatrix matrix({
        {1.0f, 2.0f, 3.0f, 4.0f},
        {5.0f, 6.0f, 7.0f, 8.0f},
        {9.0f, 8.0f, 7.0f, 6.0f},
        {5.0f, 4.0f, 3.0f, 200000.0f},
    });

    // When
    std::stringstream stream;
    stream << matrix;

    // Then
    ASSERT_EQ(stream.str(),
              "|       1.000       2.000       3.000       4.000 |\n"
              "|       5.000       6.000       7.000       8.000 |\n"
              "|       9.000       8.000       7.000       6.000 |\n"
              "|       5.000       4.000       3.000  200000.000 |\n");
}

TEST_F(NMMatrixTest, StreamInsertionOperator_FixedDecimalPrecision)
{
    // Given
    NMMatrix matrix({
        {1.3333333f, 2.6666666f, 3.63465243452f, 4.99999999999999f},
        {5.0f, 6.0f, 7.0f, 8.0f},
        {9.0f, 8.0f, 7.0f, 6.0f},
        {5.0f, 4.0f, 3.0f, 2.0f},
    });

    // When
    std::stringstream stream;
    stream << matrix;

    // Then
    ASSERT_EQ(stream.str(),
              "|  1.333  2.667  3.635  5.000 |\n"
              "|  5.000  6.000  7.000  8.000 |\n"
              "|  9.000  8.000  7.000  6.000 |\n"
              "|  5.000  4.000  3.000  2.000 |\n");
}

TEST_F(NMMatrixTest, Get)
{
    // Given
    NMMatrix matrix(2, 3);

    // Then
    ASSERT_EQ(matrix.Get(0, 0), 0.0f);
    ASSERT_EQ(matrix.Get(1, 0), 0.0f);
    ASSERT_EQ(matrix.Get(0, 1), 0.0f);
    ASSERT_EQ(matrix.Get(1, 1), 0.0f);
    ASSERT_EQ(matrix.Get(0, 2), 0.0f);
    ASSERT_EQ(matrix.Get(1, 2), 0.0f);
}

TEST_F(NMMatrixTest, Get_OutOfBounds)
{
    // Given
    NMMatrix matrix(2, 3);

    // Then
    ASSERT_TRUE(std::isnan(matrix.Get(3, 0)));
    ASSERT_TRUE(std::isnan(matrix.Get(0, 4)));
    ASSERT_TRUE(std::isnan(matrix.Get(5, 9)));
}

TEST_F(NMMatrixTest, Get_NegativeIndex)
{
    // Given
    NMMatrix matrix(2, 3);

    // Then
    ASSERT_TRUE(std::isnan(matrix.Get(-1, 0)));
    ASSERT_TRUE(std::isnan(matrix.Get(0, -1)));
    ASSERT_TRUE(std::isnan(matrix.Get(-5, -9)));
}

TEST_F(NMMatrixTest, Set)
{
    // Given
    NMMatrix matrix(2, 3);

    // When
    matrix.Set(0, 0, 1.0f);
    matrix.Set(1, 0, 2.0f);
    matrix.Set(0, 1, 3.0f);
    matrix.Set(1, 1, 4.0f);
    matrix.Set(0, 2, 5.0f);
    matrix.Set(1, 2, 6.0f);

    // Then
    ASSERT_EQ(matrix.Get(0, 0), 1.0f);
    ASSERT_EQ(matrix.Get(1, 0), 2.0f);
    ASSERT_EQ(matrix.Get(0, 1), 3.0f);
    ASSERT_EQ(matrix.Get(1, 1), 4.0f);
    ASSERT_EQ(matrix.Get(0, 2), 5.0f);
    ASSERT_EQ(matrix.Get(1, 2), 6.0f);
}

TEST_F(NMMatrixTest, Set_OutOfBounds)
{
    // Given
    NMMatrix matrix(2, 3);

    // When
    matrix.Set(3, 0, 1.0f);
    matrix.Set(0, 4, 2.0f);
    matrix.Set(5, 9, 3.0f);

    // Then
    ASSERT_EQ(matrix.Get(0, 0), 0.0f);
    ASSERT_EQ(matrix.Get(1, 0), 0.0f);
    ASSERT_EQ(matrix.Get(0, 1), 0.0f);
    ASSERT_EQ(matrix.Get(1, 1), 0.0f);
    ASSERT_EQ(matrix.Get(0, 2), 0.0f);
    ASSERT_EQ(matrix.Get(1, 2), 0.0f);
}

TEST_F(NMMatrixTest, Set_NegativeIndex)
{
    // Given
    NMMatrix matrix(2, 3);

    // When
    matrix.Set(-1, 0, 1.0f);
    matrix.Set(0, -1, 2.0f);
    matrix.Set(-5, -9, 3.0f);

    // Then
    ASSERT_EQ(matrix.Get(0, 0), 0.0f);
    ASSERT_EQ(matrix.Get(1, 0), 0.0f);
    ASSERT_EQ(matrix.Get(0, 1), 0.0f);
    ASSERT_EQ(matrix.Get(1, 1), 0.0f);
    ASSERT_EQ(matrix.Get(0, 2), 0.0f);
    ASSERT_EQ(matrix.Get(1, 2), 0.0f);
}
