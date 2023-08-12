#include <gtest/gtest.h>

#include <cmath>

#include "NMM/Matrix.hpp"
#include "NMM/Tuple.hpp"

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

TEST_F(NMMatrixTest, OperatorMultiply_Matrix)
{
    // Given
    NMMatrix matrix1({
        {1.0f, 2.0f, 3.0f, 4.0f},
        {5.0f, 6.0f, 7.0f, 8.0f},
        {9.0f, 8.0f, 7.0f, 6.0f},
        {5.0f, 4.0f, 3.0f, 2.0f},
    });

    NMMatrix matrix2({
        {-2.0f, 1.0f, 2.0f, 3.0f},
        {3.0f, 2.0f, 1.0f, -1.0f},
        {4.0f, 3.0f, 6.0f, 5.0f},
        {1.0f, 2.0f, 7.0f, 8.0f},
    });

    // When
    NMMatrix result = matrix1 * matrix2;

    // Then
    ASSERT_EQ(result.GetWidth(), 4);
    ASSERT_EQ(result.GetHeight(), 4);

    ASSERT_EQ(result.Get(0, 0), 20.0f);
    ASSERT_EQ(result.Get(1, 0), 22.0f);
    ASSERT_EQ(result.Get(2, 0), 50.0f);
    ASSERT_EQ(result.Get(3, 0), 48.0f);

    ASSERT_EQ(result.Get(0, 1), 44.0f);
    ASSERT_EQ(result.Get(1, 1), 54.0f);
    ASSERT_EQ(result.Get(2, 1), 114.0f);
    ASSERT_EQ(result.Get(3, 1), 108.0f);

    ASSERT_EQ(result.Get(0, 2), 40.0f);
    ASSERT_EQ(result.Get(1, 2), 58.0f);
    ASSERT_EQ(result.Get(2, 2), 110.0f);
    ASSERT_EQ(result.Get(3, 2), 102.0f);

    ASSERT_EQ(result.Get(0, 3), 16.0f);
    ASSERT_EQ(result.Get(1, 3), 26.0f);
    ASSERT_EQ(result.Get(2, 3), 46.0f);
    ASSERT_EQ(result.Get(3, 3), 42.0f);
}

TEST_F(NMMatrixTest, OperatorMultiply_Tuple)
{
    // Given
    NMMatrix matrix({
        {1.0f, 2.0f, 3.0f, 4.0f},
        {2.0f, 4.0f, 4.0f, 2.0f},
        {8.0f, 6.0f, 4.0f, 1.0f},
        {0.0f, 0.0f, 0.0f, 1.0f},
    });

    NMTuple tuple(1.0f, 2.0f, 3.0f, 1.0f);

    // When
    NMTuple result = matrix * tuple;

    // Then
    ASSERT_EQ(result.GetX(), 18.0f);
    ASSERT_EQ(result.GetY(), 24.0f);
    ASSERT_EQ(result.GetZ(), 33.0f);
    ASSERT_EQ(result.GetW(), 1.0f);
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

TEST_F(NMMatrixTest, Transpose)
{
    //Given
    NMMatrix matrix = NMMatrix(4, 4, {
        0.0f, 9.0f, 3.0f, 0.0f,
        9.0f, 8.0f, 0.0f, 8.0f,
        1.0f, 8.0f, 5.0f, 3.0f,
        0.0f, 0.0f, 5.0f, 8.0f,
    });

    NMMatrix expectedMatrix = NMMatrix(4, 4, {
        0.0f, 9.0f, 1.0f, 0.0f,
        9.0f, 8.0f, 8.0f, 0.0f,
        3.0f, 0.0f, 5.0f, 5.0f,
        0.0f, 8.0f, 3.0f, 8.0f,
    });

    // When
    matrix.Transpose();

    // Then
    ASSERT_EQ(matrix.GetWidth(), 4);
    ASSERT_EQ(matrix.GetHeight(), 4);

    ASSERT_EQ(matrix, expectedMatrix);
}

TEST_F(NMMatrixTest, TransposeIdentity)
{
    // Given
    NMMatrix matrix = NMMatrix::Identity4x4();

    // When
    matrix.Transpose();

    // Then
    ASSERT_EQ(matrix.GetWidth(), 4);
    ASSERT_EQ(matrix.GetHeight(), 4);

    ASSERT_EQ(matrix, NMMatrix::Identity4x4());
}

TEST_F(NMMatrixTest, Determinant_2x2)
{
    // Given
    NMMatrix matrix = NMMatrix(2, 2, {
        1.0f, 5.0f,
        -3.0f, 2.0f,
    });

    // When
    float result = matrix.Determinant();

    // Then
    ASSERT_EQ(result, 17.0f);
}

TEST_F(NMMatrixTest, Determinant_3x3)
{
    // Given
    NMMatrix matrix = NMMatrix(3, 3, {
        1.0f, 2.0f, 6.0f,
        -5.0f, 8.0f, -4.0f,
        2.0f, 6.0f, 4.0f,
    });

    // When
    float result1 = matrix.Cofactor(0, 0);
    float result2 = matrix.Cofactor(0, 1);
    float result3 = matrix.Cofactor(0, 2);
    float result4 = matrix.Determinant();

    // Then
    ASSERT_EQ(result1, 56.0f);
    ASSERT_EQ(result2, 12.0f);
    ASSERT_EQ(result3, -46.0f);
    ASSERT_EQ(result4, -196.0f);
}

TEST_F(NMMatrixTest, Determinant_4x4)
{
    // Given
    NMMatrix matrix = NMMatrix(4, 4, {
        -2.0f, -8.0f, 3.0f, 5.0f,
        -3.0f, 1.0f, 7.0f, 3.0f,
        1.0f, 2.0f, -9.0f, 6.0f,
        -6.0f, 7.0f, 7.0f, -9.0f,
    });

    // When
    float result1 = matrix.Cofactor(0, 0);
    float result2 = matrix.Cofactor(0, 1);
    float result3 = matrix.Cofactor(0, 2);
    float result4 = matrix.Cofactor(0, 3);
    float result5 = matrix.Determinant();

    // Then
    ASSERT_EQ(result1, 690.0f);
    ASSERT_EQ(result2, 447.0f);
    ASSERT_EQ(result3, 210.0f);
    ASSERT_EQ(result4, 51.0f);
    ASSERT_EQ(result5, -4071.0f);
}

TEST_F(NMMatrixTest, IsInvertible)
{
    // Given
    NMMatrix matrix1 = NMMatrix(4, 4, {
        6.0f, 4.0f, 4.0f, 4.0f,
        5.0f, 5.0f, 7.0f, 6.0f,
        4.0f, -9.0f, 3.0f, -7.0f,
        9.0f, 1.0f, 7.0f, -6.0f,
    });

    // When
    float determinant1 = matrix1.Determinant();
    bool isInvertable1 = matrix1.IsInvertible();

    // Then
    EXPECT_EQ(determinant1, -2120.0f);
    EXPECT_TRUE(isInvertable1);
}

TEST_F(NMMatrixTest, IsInvertable_False)
{
    // Given
    NMMatrix matrix = NMMatrix(4, 4, {
        -4.0f, 2.0f, -2.0f, -3.0f,
        9.0f, 6.0f, 2.0f, 6.0f,
        0.0f, -5.0f, 1.0f, -5.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
    });

    // When
    float determinant = matrix.Determinant();
    bool isInvertable = matrix.IsInvertible();

    // Then
    EXPECT_EQ(determinant, 0.0f);
    EXPECT_FALSE(isInvertable);
}

TEST_F(NMMatrixTest, Inverse)
{
    // Given
    NMMatrix matrix = NMMatrix(4, 4, {
        -5.0f, 2.0f, 6.0f, -8.0f,
        1.0f, -5.0f, 1.0f, 8.0f,
        7.0f, 7.0f, -6.0f, -7.0f,
        1.0f, -3.0f, 7.0f, 4.0f,
    });

    // When
    NMMatrix inverse = matrix.Inverse();

    // Then
    ASSERT_EQ(inverse.GetWidth(), 4);
    ASSERT_EQ(inverse.GetHeight(), 4);

    ASSERT_FLOAT_EQ(inverse.Get(0, 0), 0.218045115f);
    ASSERT_FLOAT_EQ(inverse.Get(1, 0), 0.451127819f);
    ASSERT_FLOAT_EQ(inverse.Get(2, 0), 0.240601504f);
    ASSERT_FLOAT_EQ(inverse.Get(3, 0), -0.045112781f);

    ASSERT_FLOAT_EQ(inverse.Get(0, 1), -0.808270676f);
    ASSERT_FLOAT_EQ(inverse.Get(1, 1), -1.456766917f);
    ASSERT_FLOAT_EQ(inverse.Get(2, 1), -0.443609023f);
    ASSERT_FLOAT_EQ(inverse.Get(3, 1), 0.520676692f);

    ASSERT_FLOAT_EQ(inverse.Get(0, 2), -0.078947368f);
    ASSERT_FLOAT_EQ(inverse.Get(1, 2), -0.223684211f);
    ASSERT_FLOAT_EQ(inverse.Get(2, 2), -0.052631579f);
    ASSERT_FLOAT_EQ(inverse.Get(3, 2), 0.197368421f);

    ASSERT_FLOAT_EQ(inverse.Get(0, 3), -0.522556390f);
    ASSERT_FLOAT_EQ(inverse.Get(1, 3), -0.813909774f);
    ASSERT_FLOAT_EQ(inverse.Get(2, 3), -0.300751865f);
    ASSERT_FLOAT_EQ(inverse.Get(3, 3), 0.306390977f);

    ASSERT_FLOAT_EQ(matrix.Determinant(), 532.0f);
    ASSERT_FLOAT_EQ(matrix.Cofactor(2, 3), -160.0f);
    // ASSERT_FLOAT_EQ(inverse.Get(3, 2), -160.0f / 532.0f);
    ASSERT_FLOAT_EQ(matrix.Cofactor(3, 2), 105.0f);
    // ASSERT_FLOAT_EQ(inverse.Get(2, 3), 105.0f / 532.0f);
}

TEST_F(NMMatrixTest, Inverse_B)
{
    // Given
    NMMatrix matrix = NMMatrix(4, 4, {
        8.0f, -5.0f, 9.0f, 2.0f,
        7.0f, 5.0f, 6.0f, 1.0f,
        -6.0f, 0.0f, 9.0f, 6.0f,
        -3.0f, 0.0f, -9.0f, -4.0f,
    });

    // When
    NMMatrix inverse = matrix.Inverse();

    // Then
    ASSERT_EQ(inverse.GetWidth(), 4);
    ASSERT_EQ(inverse.GetHeight(), 4);

    ASSERT_FLOAT_EQ(inverse.Get(0, 0), -0.153846153f);
    ASSERT_FLOAT_EQ(inverse.Get(1, 0), -0.153846153f);
    ASSERT_FLOAT_EQ(inverse.Get(2, 0), -0.282051282f);
    ASSERT_FLOAT_EQ(inverse.Get(3, 0), -0.538461538f);

    ASSERT_FLOAT_EQ(inverse.Get(0, 1), -0.076923077f);
    ASSERT_FLOAT_EQ(inverse.Get(1, 1), 0.123076923f);
    ASSERT_FLOAT_EQ(inverse.Get(2, 1), 0.025641026f);
    ASSERT_FLOAT_EQ(inverse.Get(3, 1), 0.030769231f);

    ASSERT_FLOAT_EQ(inverse.Get(0, 2), 0.358974359f);
    ASSERT_FLOAT_EQ(inverse.Get(1, 2), 0.358974359f);
    ASSERT_FLOAT_EQ(inverse.Get(2, 2), 0.435897436f);
    ASSERT_FLOAT_EQ(inverse.Get(3, 2), 0.923076923f);

    ASSERT_FLOAT_EQ(inverse.Get(0, 3), -0.692307692f);
    ASSERT_FLOAT_EQ(inverse.Get(1, 3), -0.692307692f);
    ASSERT_FLOAT_EQ(inverse.Get(2, 3), -0.769230769f);
    ASSERT_FLOAT_EQ(inverse.Get(3, 3), -1.923076923f);
}

TEST_F(NMMatrixTest, Inverse_C)
{
    // Given
    NMMatrix matrix = NMMatrix(4, 4, {
        9.0f, 3.0f, 0.0f, 9.0f,
        -5.0f, -2.0f, -6.0f, -3.0f,
        -4.0f, 9.0f, 6.0f, 4.0f,
        -7.0f, 6.0f, 6.0f, 2.0f,
    });

    // When
    NMMatrix inverse = matrix.Inverse();

    // Then
    ASSERT_EQ(inverse.GetWidth(), 4);
    ASSERT_EQ(inverse.GetHeight(), 4);

    ASSERT_FLOAT_EQ(inverse.Get(0, 0), -0.040740741f);
    ASSERT_FLOAT_EQ(inverse.Get(1, 0), -0.077777778f);
    ASSERT_FLOAT_EQ(inverse.Get(2, 0), 0.144444444f);
    ASSERT_FLOAT_EQ(inverse.Get(3, 0), -0.222222222f);

    ASSERT_FLOAT_EQ(inverse.Get(0, 1), -0.077777778f);
    ASSERT_FLOAT_EQ(inverse.Get(1, 1), 0.033333333f);
    ASSERT_FLOAT_EQ(inverse.Get(2, 1), 0.366666667f);
    ASSERT_FLOAT_EQ(inverse.Get(3, 1), -0.333333333f);

    ASSERT_FLOAT_EQ(inverse.Get(0, 2), -0.029012346f);
    ASSERT_FLOAT_EQ(inverse.Get(1, 2), -0.146296296f);
    ASSERT_FLOAT_EQ(inverse.Get(2, 2), -0.109259259f);
    ASSERT_FLOAT_EQ(inverse.Get(3, 2), 0.129629630f);

    ASSERT_FLOAT_EQ(inverse.Get(0, 3), 0.177777778f);
    ASSERT_FLOAT_EQ(inverse.Get(1, 3), 0.066666667f);
    ASSERT_FLOAT_EQ(inverse.Get(2, 3), -0.266666667f);
    ASSERT_FLOAT_EQ(inverse.Get(3, 3), 0.333333333f);
}

TEST_F(NMMatrixTest, Inverse_Multiply)
{
    // Given
    NMMatrix matrixA = NMMatrix(4, 4, {
        3.0f, -9.0f, 7.0f, 3.0f,
        3.0f, -8.0f, 2.0f, -9.0f,
        -4.0f, 4.0f, 4.0f, 1.0f,
        -6.0f, 5.0f, -1.0f, 1.0f,
    });

    NMMatrix matrixB = NMMatrix(4, 4, {
        8.0f, 2.0f, 2.0f, 2.0f,
        3.0f, -1.0f, 7.0f, 0.0f,
        7.0f, 0.0f, 5.0f, 4.0f,
        6.0f, -2.0f, 0.0f, 5.0f,
    });

    NMMatrix matrixAB = matrixA * matrixB;

    // When
    NMMatrix matrixBInverse = matrixB.Inverse();

    // Then
    EXPECT_EQ(matrixAB * matrixBInverse, matrixA);
}

TEST_F(NMMatrixTest, Submatrix_4x4)
{
    // Given
    NMMatrix matrix = NMMatrix(4, 4, {
        -6.0f, 1.0f, 1.0f, 6.0f,
        -8.0f, 5.0f, 8.0f, 6.0f,
        -1.0f, 0.0f, 8.0f, 2.0f,
        -7.0f, 1.0f, -1.0f, 1.0f,
    });

    NMMatrix expectedMatrix = NMMatrix(3, 3, {
        -6.0f, 1.0f, 6.0f,
        -8.0f, 8.0f, 6.0f,
        -7.0f, -1.0f, 1.0f,
    });

    // When
    NMMatrix result = matrix.Submatrix(2, 1);

    // Then
    ASSERT_EQ(result.GetWidth(), 3);
    ASSERT_EQ(result.GetHeight(), 3);

    ASSERT_EQ(result, expectedMatrix);
}

TEST_F(NMMatrixTest, Submatrix_3x3)
{
    // Given
    NMMatrix matrix = NMMatrix(3, 3, {
        1.0f, 5.0f, 0.0f,
        -3.0f, 2.0f, 7.0f,
        0.0f, 6.0f, -3.0f,
    });

    NMMatrix expectedMatrix = NMMatrix(2, 2, {
        -3.0f, 2.0f,
        0.0f, 6.0f,
    });

    // When
    NMMatrix result = matrix.Submatrix(0, 2);

    // Then
    ASSERT_EQ(result.GetWidth(), 2);
    ASSERT_EQ(result.GetHeight(), 2);

    ASSERT_EQ(result, expectedMatrix);
}

TEST_F(NMMatrixTest, Minor)
{
    // Given
    NMMatrix matrix = NMMatrix(3, 3, {
        3.0f, 5.0f, 0.0f,
        2.0f, -1.0f, -7.0f,
        6.0f, -1.0f, 5.0f,
    });

    // When
    float result = matrix.Minor(1, 0);

    // Then
    ASSERT_EQ(result, 25.0f);
}

TEST_F(NMMatrixTest, Cofactor)
{
    // Given
    NMMatrix matrix = NMMatrix(3, 3, {
        3.0f, 5.0f, 0.0f,
        2.0f, -1.0f, -7.0f,
        6.0f, -1.0f, 5.0f,
    });

    // When
    float result1 = matrix.Minor(0, 0);
    float result2 = matrix.Cofactor(0, 0);
    float result3 = matrix.Minor(1, 0);
    float result4 = matrix.Cofactor(1, 0);

    // Then
    ASSERT_EQ(result1, -12.0f);
    ASSERT_EQ(result2, -12.0f);
    ASSERT_EQ(result3, 25.0f);
    ASSERT_EQ(result4, -25.0f);
}

TEST_F(NMMatrixTest, Identity3x3)
{
    // Given
    NMMatrix matrix = NMMatrix(3, 3, {
        0.0f, 1.0f, 2.0f,
        1.0f, 2.0f, 4.0f,
        2.0f, 4.0f, 8.0f,
    });

    // When
    NMMatrix result = matrix * NMMatrix::Identity3x3();

    // Then
    ASSERT_EQ(result.GetWidth(), 3);
    ASSERT_EQ(result.GetHeight(), 3);

    ASSERT_EQ(result, matrix);
}

TEST_F(NMMatrixTest, Identity4x4)
{
    // Given
    NMMatrix matrix = NMMatrix(4, 4, {
        0.0f, 1.0f, 2.0f, 4.0f,
        1.0f, 2.0f, 4.0f, 8.0f,
        2.0f, 4.0f, 8.0f, 16.0f,
        4.0f, 8.0f, 16.0f, 32.0f,
    });

    // When
    NMMatrix result = matrix * NMMatrix::Identity4x4();

    // Then
    ASSERT_EQ(result.GetWidth(), 4);
    ASSERT_EQ(result.GetHeight(), 4);

    ASSERT_EQ(result, matrix);
}
