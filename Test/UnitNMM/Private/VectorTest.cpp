#include <gtest/gtest.h>

#include <cmath>

#include "NMM/Point.hpp"
#include "NMM/Tuple.hpp"
#include "NMM/Vector.hpp"

class NMVectorTest : public ::testing::Test
{
};

TEST_F(NMVectorTest, VectorCreation_Default)
{
    // Given
    NMVector vector;

    // Then
    EXPECT_FLOAT_EQ(vector.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(vector.GetY(), 0.0f);
    EXPECT_FLOAT_EQ(vector.GetZ(), 0.0f);
}

TEST_F(NMVectorTest, VectorCreation)
{
    // Given
    NMVector vector(4.3f, -4.2f, 3.1f);

    // Then
    EXPECT_FLOAT_EQ(vector.GetX(), 4.3f);
    EXPECT_FLOAT_EQ(vector.GetY(), -4.2f);
    EXPECT_FLOAT_EQ(vector.GetZ(), 3.1f);
}

TEST_F(NMVectorTest, VectorCreation_FromTuple)
{
    // Given
    NMTuple tuple(4.3f, -4.2f, 3.1f, 0.0f);
    NMVector vector(tuple);

    // Then
    EXPECT_FLOAT_EQ(vector.GetX(), 4.3f);
    EXPECT_FLOAT_EQ(vector.GetY(), -4.2f);
    EXPECT_FLOAT_EQ(vector.GetZ(), 3.1f);
}

TEST_F(NMVectorTest, VectorCreation_FromTuple_Point)
{
    // Given
    NMTuple tuple(4.3f, -4.2f, 3.1f, 1.0f);
    NMVector vector(tuple);

    // Then
    EXPECT_FLOAT_EQ(vector.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(vector.GetY(), 0.0f);
    EXPECT_FLOAT_EQ(vector.GetZ(), 0.0f);
}

TEST_F(NMVectorTest, AddOperator_Point)
{
    // Given
    NMVector vector(3.0f, -2.0f, 5.0f);
    NMPoint point(-2.0f, 3.0f, 1.0f);

    // When
    NMPoint result = vector + point;

    // Then
    EXPECT_EQ(result, NMPoint(1.0f, 1.0f, 6.0f));
}

TEST_F(NMVectorTest, AddOperator_Vector)
{
    // Given
    NMVector vector1(3.0f, -2.0f, 5.0f);
    NMVector vector2(-2.0f, 3.0f, 1.0f);

    // When
    NMVector result = vector1 + vector2;

    // Then
    EXPECT_EQ(result, NMVector(1.0f, 1.0f, 6.0f));
}

TEST_F(NMVectorTest, SubtractOperator_Vector)
{
    // Given
    NMVector vector1(3.0f, -2.0f, 5.0f);
    NMVector vector2(-2.0f, 3.0f, 1.0f);

    // When
    NMVector result = vector1 - vector2;

    // Then
    EXPECT_EQ(result, NMVector(5.0f, -5.0f, 4.0f));
}

TEST_F(NMVectorTest, NegateOperator)
{
    // Given
    NMVector vector(1.0f, -2.0f, 3.0f);

    // When
    NMVector result = -vector;

    // Then
    EXPECT_EQ(result, NMVector(-1.0f, 2.0f, -3.0f));
}

TEST_F(NMVectorTest, MultiplyOperator_Scalar)
{
    // Given
    NMVector vector(1.0f, -2.0f, 3.0f);

    // When
    NMVector result = vector * 3.5f;

    // Then
    EXPECT_EQ(result, NMVector(3.5f, -7.0f, 10.5f));
}

TEST_F(NMVectorTest, MultiplyOperator_Fraction)
{
    // Given
    NMVector vector(1.0f, -2.0f, 3.0f);

    // When
    NMVector result = vector * 0.5f;

    // Then
    EXPECT_EQ(result, NMVector(0.5f, -1.0f, 1.5f));
}

TEST_F(NMVectorTest, MultiplyEqualOperator_Scalar)
{
    // Given
    NMVector vector(1.0f, -2.0f, 3.0f);

    // When
    vector *= 3.5f;

    // Then
    EXPECT_EQ(vector, NMVector(3.5f, -7.0f, 10.5f));
}

TEST_F(NMVectorTest, MultiplyEqualOperator_Fraction)
{
    // Given
    NMVector vector(1.0f, -2.0f, 3.0f);

    // When
    vector *= 0.5f;

    // Then
    EXPECT_EQ(vector, NMVector(0.5f, -1.0f, 1.5f));
}

TEST_F(NMVectorTest, DivideOperator_Scalar)
{
    // Given
    NMVector vector(1.0f, -2.0f, 3.0f);

    // When
    NMVector result = vector / 2.0f;

    // Then
    EXPECT_EQ(result, NMVector(0.5f, -1.0f, 1.5f));
}

TEST_F(NMVectorTest, AddAssignOperator_Vector)
{
    // Given
    NMVector vector1(3.0f, -2.0f, 5.0f);
    NMVector vector2(-2.0f, 3.0f, 1.0f);

    // When
    vector1 += vector2;

    // Then
    EXPECT_EQ(vector1, NMVector(1.0f, 1.0f, 6.0f));
}

TEST_F(NMVectorTest, SubtractAssignOperator_Vector)
{
    // Given
    NMVector vector1(3.0f, -2.0f, 5.0f);
    NMVector vector2(-2.0f, 3.0f, 1.0f);

    // When
    vector1 -= vector2;

    // Then
    EXPECT_EQ(vector1, NMVector(5.0f, -5.0f, 4.0f));
}

TEST_F(NMVectorTest, DivideAssignOperator_Scalar)
{
    // Given
    NMVector vector(1.0f, -2.0f, 3.0f);

    // When
    vector /= 2.0f;

    // Then
    EXPECT_EQ(vector, NMVector(0.5f, -1.0f, 1.5f));
}

TEST_F(NMVectorTest, StreamInsertionOperator)
{
    // Given
    NMVector vector(1.0f, -2.0f, 3.0f);
    std::stringstream stream;

    // When
    stream << vector;

    // Then
    EXPECT_EQ(stream.str(), "(1.00, -2.00, 3.00)");
}

TEST_F(NMVectorTest, StreamInsertionOperator_LimitedPrecision)
{
    // Given
    NMVector vector(1.0f / 3.0f, -2.0f / 3.0f, 1.0f);
    std::stringstream stream;

    // When
    stream << vector;

    // Then
    EXPECT_EQ(stream.str(), "(0.33, -0.67, 1.00)");
}

TEST_F(NMVectorTest, StreamInsertionOperator_Infinity)
{
    // Given
    NMVector vector(1.0f, std::numeric_limits<float>::infinity() * -1, std::numeric_limits<float>::infinity());
    std::stringstream stream;

    // When
    stream << vector;

    // Then
    EXPECT_EQ(stream.str(), "(1.00, -inf, inf)");
}

TEST_F(NMVectorTest, StreamInsertionOperator_NaN)
{
    // Given
    NMVector vector(1.0f, -2.0f, std::numeric_limits<float>::quiet_NaN());
    std::stringstream stream;

    // When
    stream << vector;

    // Then
    EXPECT_EQ(stream.str(), "(1.00, -2.00, nan)");
}

TEST_F(NMVectorTest, SquaredMagnitude)
{
    // Given
    NMVector vector1(1.0f, 0.0f, 0.0f);
    NMVector vector2(0.0f, 1.0f, 0.0f);
    NMVector vector3(0.0f, 0.0f, 1.0f);
    NMVector vector4(1.0f, 2.0f, 3.0f);
    NMVector vector5(-1.0f, -2.0f, -3.0f);

    // Then
    EXPECT_FLOAT_EQ(vector1.SquaredMagnitude(), 1.0f);
    EXPECT_FLOAT_EQ(vector2.SquaredMagnitude(), 1.0f);
    EXPECT_FLOAT_EQ(vector3.SquaredMagnitude(), 1.0f);
    EXPECT_FLOAT_EQ(vector4.SquaredMagnitude(), 14.0f);
    EXPECT_FLOAT_EQ(vector5.SquaredMagnitude(), 14.0f);
}

TEST_F(NMVectorTest, Magnitude)
{
    // Given
    NMVector vector1(1.0f, 0.0f, 0.0f);
    NMVector vector2(0.0f, 1.0f, 0.0f);
    NMVector vector3(0.0f, 0.0f, 1.0f);
    NMVector vector4(1.0f, 2.0f, 3.0f);
    NMVector vector5(-1.0f, -2.0f, -3.0f);

    // Then
    EXPECT_FLOAT_EQ(vector1.Magnitude(), 1.0f);
    EXPECT_FLOAT_EQ(vector2.Magnitude(), 1.0f);
    EXPECT_FLOAT_EQ(vector3.Magnitude(), 1.0f);
    EXPECT_FLOAT_EQ(vector4.Magnitude(), std::sqrt(14.0f));
    EXPECT_FLOAT_EQ(vector5.Magnitude(), std::sqrt(14.0f));
}

TEST_F(NMVectorTest, Normalized)
{
    // Given
    NMVector vector1(4.0f, 0.0f, 0.0f);
    NMVector vector2(1.0f, 2.0f, 3.0f);

    // When
    NMVector result1 = vector1.Normalized();
    NMVector result2 = vector2.Normalized();

    // Then
    EXPECT_EQ(result1, NMVector(1.0f, 0.0f, 0.0f));
    EXPECT_EQ(result2, NMVector(1.0f / std::sqrt(14.0f), 2.0f / std::sqrt(14.0f), 3.0f / std::sqrt(14.0f)));
}

TEST_F(NMVectorTest, Normalize)
{
    // Given
    NMVector vector1(4.0f, 0.0f, 0.0f);
    NMVector vector2(1.0f, 2.0f, 3.0f);

    // When
    vector1.Normalize();
    vector2.Normalize();

    // Then
    EXPECT_EQ(vector1, NMVector(1.0f, 0.0f, 0.0f));
    EXPECT_EQ(vector2, NMVector(1.0f / std::sqrt(14.0f), 2.0f / std::sqrt(14.0f), 3.0f / std::sqrt(14.0f)));
}

TEST_F(NMVectorTest, DotProduct)
{
    // Given
    NMVector vector1(1.0f, 2.0f, 3.0f);
    NMVector vector2(2.0f, 3.0f, 4.0f);

    // When
    float result = vector1.DotProduct(vector2);

    // Then
    EXPECT_FLOAT_EQ(result, 20.0f);
}

TEST_F(NMVectorTest, DotProduct_Point)
{
    // Given
    NMVector vector(1.0f, 2.0f, 3.0f);
    NMPoint point(2.0f, 3.0f, 4.0f);

    // When
    float result = vector.DotProduct(point);

    // Then
    EXPECT_FLOAT_EQ(result, 20.0f);
}

TEST_F(NMVectorTest, CrossProduct)
{
    // Given
    NMVector vector1(1.0f, 2.0f, 3.0f);
    NMVector vector2(2.0f, 3.0f, 4.0f);

    // When
    NMVector result1 = vector1.CrossProduct(vector2);
    NMVector result2 = vector2.CrossProduct(vector1);

    // Then
    EXPECT_EQ(result1, NMVector(-1.0f, 2.0f, -1.0f));
    EXPECT_EQ(result2, NMVector(1.0f, -2.0f, 1.0f));
}

// Scenario: Reflecting a vector approaching at 45°
TEST_F(NMVectorTest, Reflect_45)
{
    // Given
    NMVector vector(1.0f, -1.0f, 0.0f);
    NMVector normal(0.0f, 1.0f, 0.0f);

    // When
    NMVector result = vector.Reflect(normal);

    // Then
    EXPECT_EQ(result, NMVector(1.0f, 1.0f, 0.0f));
}

// Scenario: Reflecting a vector off a slanted surface
TEST_F(NMVectorTest, Reflect_Slanted)
{
    // Given
    NMVector vector(0.0f, -1.0f, 0.0f);
    NMVector normal(std::sqrt(2.0f) / 2.0f, std::sqrt(2.0f) / 2.0f, 0.0f);

    // When
    NMVector result = vector.Reflect(normal);

    // Then
    EXPECT_EQ(result, NMVector(1.0f, 0.0f, 0.0f));
}
