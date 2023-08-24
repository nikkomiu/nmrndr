#include <gtest/gtest.h>

#include "NMM/Point.hpp"
#include "NMM/Tuple.hpp"

class NMPointTest : public ::testing::Test
{
};

TEST_F(NMPointTest, PointCreation_Default)
{
    // Given
    NMPoint point;

    // Then
    EXPECT_FLOAT_EQ(point.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(point.GetY(), 0.0f);
    EXPECT_FLOAT_EQ(point.GetZ(), 0.0f);
}

TEST_F(NMPointTest, PointCreation)
{
    // Given
    NMPoint point(4.3f, -4.2f, 3.1f);

    // Then
    EXPECT_FLOAT_EQ(point.GetX(), 4.3f);
    EXPECT_FLOAT_EQ(point.GetY(), -4.2f);
    EXPECT_FLOAT_EQ(point.GetZ(), 3.1f);
}

TEST_F(NMPointTest, PointCreation_FromTuple)
{
    // Given
    NMTuple tuple(4.3f, -4.2f, 3.1f, 1.0f);
    NMPoint point(tuple);

    // Then
    EXPECT_FLOAT_EQ(point.GetX(), 4.3f);
    EXPECT_FLOAT_EQ(point.GetY(), -4.2f);
    EXPECT_FLOAT_EQ(point.GetZ(), 3.1f);
}

TEST_F(NMPointTest, PointCreation_FromTuple_Vector)
{
    // Given
    NMTuple tuple(4.3f, -4.2f, 3.1f, 0.0f);
    NMPoint point(tuple);

    // Then
    EXPECT_FLOAT_EQ(point.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(point.GetY(), 0.0f);
    EXPECT_FLOAT_EQ(point.GetZ(), 0.0f);
}

TEST_F(NMPointTest, AddOperator_Vector)
{
    // Given
    NMPoint point(3.0f, -2.0f, 5.0f);
    NMVector vector(-2.0f, 3.0f, 1.0f);

    // When
    NMPoint result = point + vector;

    // Then
    EXPECT_FLOAT_EQ(result.GetX(), 1.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 1.0f);
    EXPECT_FLOAT_EQ(result.GetZ(), 6.0f);
}

TEST_F(NMPointTest, SubtractOperator_Point)
{
    // Given
    NMPoint point1(3.0f, 2.0f, 1.0f);
    NMPoint point2(5.0f, 6.0f, 7.0f);

    // When
    NMVector result = point1 - point2;

    // Then
    EXPECT_FLOAT_EQ(result.GetX(), -2.0f);
    EXPECT_FLOAT_EQ(result.GetY(), -4.0f);
    EXPECT_FLOAT_EQ(result.GetZ(), -6.0f);
}

TEST_F(NMPointTest, SubtractOperator_Vector)
{
    // Given
    NMPoint point(3.0f, 2.0f, 1.0f);
    NMVector vector(5.0f, 6.0f, 7.0f);

    // When
    NMPoint result = point - vector;

    // Then
    EXPECT_FLOAT_EQ(result.GetX(), -2.0f);
    EXPECT_FLOAT_EQ(result.GetY(), -4.0f);
    EXPECT_FLOAT_EQ(result.GetZ(), -6.0f);
}

TEST_F(NMPointTest, NegateOperator)
{
    // Given
    NMPoint point(1.0f, -2.0f, 3.0f);

    // When
    NMPoint result = -point;

    // Then
    EXPECT_FLOAT_EQ(result.GetX(), -1.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 2.0f);
    EXPECT_FLOAT_EQ(result.GetZ(), -3.0f);
}

TEST_F(NMPointTest, AddAssignOperator_Vector)
{
    // Given
    NMPoint point(3.0f, -2.0f, 5.0f);
    NMVector vector(-2.0f, 3.0f, 1.0f);

    // When
    point += vector;

    // Then
    EXPECT_FLOAT_EQ(point.GetX(), 1.0f);
    EXPECT_FLOAT_EQ(point.GetY(), 1.0f);
    EXPECT_FLOAT_EQ(point.GetZ(), 6.0f);
}

TEST_F(NMPointTest, AddAssignOperator_Point)
{
    // Given
    NMPoint point1(3.0f, -2.0f, 5.0f);
    NMPoint point2(-2.0f, 3.0f, 1.0f);

    // When
    point1 += point2;

    // Then
    EXPECT_FLOAT_EQ(point1.GetX(), 1.0f);
    EXPECT_FLOAT_EQ(point1.GetY(), 1.0f);
    EXPECT_FLOAT_EQ(point1.GetZ(), 6.0f);
}

TEST_F(NMPointTest, SubtractAssignOperator_Vector)
{
    // Given
    NMPoint point(3.0f, -2.0f, 5.0f);
    NMVector vector(-2.0f, 3.0f, 1.0f);

    // When
    point -= vector;

    // Then
    EXPECT_FLOAT_EQ(point.GetX(), 5.0f);
    EXPECT_FLOAT_EQ(point.GetY(), -5.0f);
    EXPECT_FLOAT_EQ(point.GetZ(), 4.0f);
}

TEST_F(NMPointTest, StreamInsertionOperator)
{
    // Given
    NMPoint point(1.0f, 2.0f, 3.0f);

    // When
    std::stringstream ss;
    ss << point;

    // Then
    EXPECT_EQ(ss.str(), "(1.00, 2.00, 3.00)");
}

TEST_F(NMPointTest, StreamInsertionOperator_LimitedPrecision)
{
    // Given
    NMPoint point(1.0f / 3.0f, -2.0f / 3.0f, 1.0f);

    // When
    std::stringstream ss;
    ss << std::setprecision(2) << point;

    // Then
    EXPECT_EQ(ss.str(), "(0.33, -0.67, 1.00)");
}

TEST_F(NMPointTest, StreamInsertionOperator_Infinity)
{
    // Given
    NMPoint point(1.0f, std::numeric_limits<float>::infinity() * -1, std::numeric_limits<float>::infinity());

    // When
    std::stringstream ss;
    ss << point;

    // Then
    EXPECT_EQ(ss.str(), "(1.00, -inf, inf)");
}

TEST_F(NMPointTest, StreamInsertionOperator_NaN)
{
    // Given
    NMPoint point(std::numeric_limits<float>::quiet_NaN(), 1.0f, 1.0f);

    // When
    std::stringstream ss;
    ss << point;

    // Then
    EXPECT_EQ(ss.str(), "(nan, 1.00, 1.00)");
}

TEST_F(NMPointTest, DotProduct)
{
    // Given
    NMPoint point1(1.0f, 2.0f, 3.0f);
    NMPoint point2(2.0f, 3.0f, 4.0f);

    // When
    float result = point1.DotProduct(point2);

    // Then
    EXPECT_FLOAT_EQ(result, 20.0f);
}
