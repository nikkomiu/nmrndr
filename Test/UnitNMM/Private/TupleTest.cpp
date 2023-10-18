#include <gtest/gtest.h>

#include "NMM/Tuple.hpp"

class NMTupleTest : public testing::Test
{
};

#pragma region Constructors

TEST_F(NMTupleTest, TupleCreation_Default)
{
    // Given
    NMTuple tuple;

    // Then
    EXPECT_FLOAT_EQ(tuple.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(tuple.GetY(), 0.0f);
    EXPECT_FLOAT_EQ(tuple.GetZ(), 0.0f);
    EXPECT_FLOAT_EQ(tuple.GetW(), 0.0f);
}

TEST_F(NMTupleTest, TupleCreation_Point)
{
    // Given
    NMTuple tuple(4.3f, -4.2f, 3.1f, 1.0f);

    // Then
    EXPECT_FLOAT_EQ(tuple.GetX(), 4.3f);
    EXPECT_FLOAT_EQ(tuple.GetY(), -4.2f);
    EXPECT_FLOAT_EQ(tuple.GetZ(), 3.1f);
    EXPECT_FLOAT_EQ(tuple.GetW(), 1.0f);
}

TEST_F(NMTupleTest, TupleCreation_Vector)
{
    // Given
    NMTuple tuple(4.3f, -4.2f, 3.1f, 0.0f);

    // Then
    EXPECT_FLOAT_EQ(tuple.GetX(), 4.3f);
    EXPECT_FLOAT_EQ(tuple.GetY(), -4.2f);
    EXPECT_FLOAT_EQ(tuple.GetZ(), 3.1f);
    EXPECT_FLOAT_EQ(tuple.GetW(), 0.0f);
}

TEST_F(NMTupleTest, CreatePoint)
{
    // Given
    NMTuple tuple = NMTuple::CreatePoint(4.3f, -4.2f, 3.1f);

    // Then
    EXPECT_FLOAT_EQ(tuple.GetX(), 4.3f);
    EXPECT_FLOAT_EQ(tuple.GetY(), -4.2f);
    EXPECT_FLOAT_EQ(tuple.GetZ(), 3.1f);
    EXPECT_FLOAT_EQ(tuple.GetW(), 1.0f);
}

TEST_F(NMTupleTest, CreateVector)
{
    // Given
    NMTuple tuple = NMTuple::CreateVector(4.3f, -4.2f, 3.1f);

    // Then
    EXPECT_FLOAT_EQ(tuple.GetX(), 4.3f);
    EXPECT_FLOAT_EQ(tuple.GetY(), -4.2f);
    EXPECT_FLOAT_EQ(tuple.GetZ(), 3.1f);
    EXPECT_FLOAT_EQ(tuple.GetW(), 0.0f);
}

TEST_F(NMTupleTest, TupleCreation_FromPoint)
{
    // Given
    NMPoint point(4.3f, -4.2f, 3.1f);
    NMTuple tuple(point);

    // Then
    EXPECT_FLOAT_EQ(tuple.GetX(), 4.3f);
    EXPECT_FLOAT_EQ(tuple.GetY(), -4.2f);
    EXPECT_FLOAT_EQ(tuple.GetZ(), 3.1f);
    EXPECT_FLOAT_EQ(tuple.GetW(), 1.0f);
}

TEST_F(NMTupleTest, TupleCreation_FromVector)
{
    // Given
    NMVector vector(4.3f, -4.2f, 3.1f);
    NMTuple tuple(vector);

    // Then
    EXPECT_FLOAT_EQ(tuple.GetX(), 4.3f);
    EXPECT_FLOAT_EQ(tuple.GetY(), -4.2f);
    EXPECT_FLOAT_EQ(tuple.GetZ(), 3.1f);
    EXPECT_FLOAT_EQ(tuple.GetW(), 0.0f);
}

#pragma endregion

#pragma region Operator Tests

TEST_F(NMTupleTest, AssignmentOperator_Point)
{
    // Given
    NMPoint point(4.3f, -4.2f, 3.1f);
    NMTuple tuple = point;

    // Then
    EXPECT_FLOAT_EQ(tuple.GetX(), 4.3f);
    EXPECT_FLOAT_EQ(tuple.GetY(), -4.2f);
    EXPECT_FLOAT_EQ(tuple.GetZ(), 3.1f);
    EXPECT_FLOAT_EQ(tuple.GetW(), 1.0f);
}

TEST_F(NMTupleTest, AssignmentOperator_Vector)
{
    // Given
    NMVector vector(4.3f, -4.2f, 3.1f);
    NMTuple tuple = vector;

    // Then
    EXPECT_FLOAT_EQ(tuple.GetX(), 4.3f);
    EXPECT_FLOAT_EQ(tuple.GetY(), -4.2f);
    EXPECT_FLOAT_EQ(tuple.GetZ(), 3.1f);
    EXPECT_FLOAT_EQ(tuple.GetW(), 0.0f);
}

TEST_F(NMTupleTest, EqualityOperator)
{
    // Given
    NMTuple tuple1(4.3f, -4.2f, 3.1f, 1.0f);
    NMTuple tuple2(4.3f, -4.2f, 3.1f, 1.0f);

    // Then
    EXPECT_TRUE(tuple1 == tuple2);
}

TEST_F(NMTupleTest, EqualityOperator_XFalse)
{
    // Given
    NMTuple tuple1(4.3f, -4.2f, 3.1f, 1.0f);
    NMTuple tuple2(4.2f, -4.2f, 3.1f, 1.0f);

    // Then
    EXPECT_FALSE(tuple1 == tuple2);
}

TEST_F(NMTupleTest, EqualityOperator_YFalse)
{
    // Given
    NMTuple tuple1(4.3f, -4.2f, 3.1f, 1.0f);
    NMTuple tuple2(4.3f, -4.3f, 3.1f, 1.0f);

    // Then
    EXPECT_FALSE(tuple1 == tuple2);
}

TEST_F(NMTupleTest, EqualityOperator_ZFalse)
{
    // Given
    NMTuple tuple1(4.3f, -4.2f, 3.1f, 1.0f);
    NMTuple tuple2(4.3f, -4.2f, 3.2f, 0.0f);

    // Then
    EXPECT_FALSE(tuple1 == tuple2);
}

TEST_F(NMTupleTest, EqualityOperator_WFalse)
{
    // Given
    NMTuple tuple1(4.3f, -4.2f, 3.1f, 1.0f);
    NMTuple tuple2(4.3f, -4.2f, 3.1f, 0.0f);

    // Then
    EXPECT_FALSE(tuple1 == tuple2);
}

TEST_F(NMTupleTest, EqualityOperator_Point)
{
    // Given
    NMPoint point(4.3f, -4.2f, 3.1f);
    NMTuple tuple(4.3f, -4.2f, 3.1f, 1.0f);

    // Then
    EXPECT_TRUE(tuple == point);
}

TEST_F(NMTupleTest, EqualityOperator_Point_XFalse)
{
    // Given
    NMPoint point(4.3f, -4.2f, 3.1f);
    NMTuple tuple(4.2f, -4.2f, 3.1f, 1.0f);

    // Then
    EXPECT_FALSE(tuple == point);
}

TEST_F(NMTupleTest, EqualityOperator_Point_YFalse)
{
    // Given
    NMPoint point(4.3f, -4.2f, 3.1f);
    NMTuple tuple(4.3f, -4.3f, 3.1f, 1.0f);

    // Then
    EXPECT_FALSE(tuple == point);
}

TEST_F(NMTupleTest, EqualityOperator_Point_ZFalse)
{
    // Given
    NMPoint point(4.3f, -4.2f, 3.1f);
    NMTuple tuple(4.3f, -4.2f, 3.2f, 1.0f);

    // Then
    EXPECT_FALSE(tuple == point);
}

TEST_F(NMTupleTest, EqualityOperator_Point_WFalse)
{
    // Given
    NMPoint point(4.3f, -4.2f, 3.1f);
    NMTuple tuple(4.3f, -4.2f, 3.1f, 0.0f);

    // Then
    EXPECT_FALSE(tuple == point);
}

TEST_F(NMTupleTest, EqualityOperator_Vector)
{
    // Given
    NMVector vector(4.3f, -4.2f, 3.1f);
    NMTuple tuple(4.3f, -4.2f, 3.1f, 0.0f);

    // Then
    EXPECT_TRUE(tuple == vector);
}

TEST_F(NMTupleTest, EqualityOperator_Vector_XFalse)
{
    // Given
    NMVector vector(4.3f, -4.2f, 3.1f);
    NMTuple tuple(4.2f, -4.2f, 3.1f, 0.0f);

    // Then
    EXPECT_FALSE(tuple == vector);
}

TEST_F(NMTupleTest, EqualityOperator_Vector_YFalse)
{
    // Given
    NMVector vector(4.3f, -4.2f, 3.1f);
    NMTuple tuple(4.3f, -4.3f, 3.1f, 0.0f);

    // Then
    EXPECT_FALSE(tuple == vector);
}

TEST_F(NMTupleTest, EqualityOperator_Vector_ZFalse)
{
    // Given
    NMVector vector(4.3f, -4.2f, 3.1f);
    NMTuple tuple(4.3f, -4.2f, 3.2f, 0.0f);

    // Then
    EXPECT_FALSE(tuple == vector);
}

TEST_F(NMTupleTest, EqualityOperator_Vector_WFalse)
{
    // Given
    NMVector vector(4.3f, -4.2f, 3.1f);
    NMTuple tuple(4.3f, -4.2f, 3.1f, 1.0f);

    // Then
    EXPECT_FALSE(tuple == vector);
}

TEST_F(NMTupleTest, AdditionOperator_PointVector)
{
    // Given
    NMTuple tuple1(3.0f, -2.0f, 5.0f, 1.0f);
    NMTuple tuple2(-2.0f, 3.0f, 1.0f, 0.0f);

    // When
    NMTuple result = tuple1 + tuple2;

    // Then
    EXPECT_FLOAT_EQ(result.GetX(), 1.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 1.0f);
    EXPECT_FLOAT_EQ(result.GetZ(), 6.0f);
    EXPECT_FLOAT_EQ(result.GetW(), 1.0f);
}

TEST_F(NMTupleTest, AdditionOperator_VectorVector)
{
    // Given
    NMTuple tuple1(3.0f, -2.0f, 5.0f, 0.0f);
    NMTuple tuple2(-2.0f, 3.0f, 1.0f, 0.0f);

    // When
    NMTuple result = tuple1 + tuple2;

    // Then
    EXPECT_FLOAT_EQ(result.GetX(), 1.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 1.0f);
    EXPECT_FLOAT_EQ(result.GetZ(), 6.0f);
    EXPECT_FLOAT_EQ(result.GetW(), 0.0f);
}

TEST_F(NMTupleTest, SubtractionOperator_PointPoint)
{
    // Given
    NMTuple tuple1(3.0f, 2.0f, 1.0f, 1.0f);
    NMTuple tuple2(5.0f, 6.0f, 7.0f, 1.0f);

    // When
    NMTuple result = tuple1 - tuple2;

    // Then
    EXPECT_FLOAT_EQ(result.GetX(), -2.0f);
    EXPECT_FLOAT_EQ(result.GetY(), -4.0f);
    EXPECT_FLOAT_EQ(result.GetZ(), -6.0f);
    EXPECT_FLOAT_EQ(result.GetW(), 0.0f);
}

TEST_F(NMTupleTest, SubtractionOperator_PointVector)
{
    // Given
    NMTuple tuple1(3.0f, 2.0f, 1.0f, 1.0f);
    NMTuple tuple2(5.0f, 6.0f, 7.0f, 0.0f);

    // When
    NMTuple result = tuple1 - tuple2;

    // Then
    EXPECT_FLOAT_EQ(result.GetX(), -2.0f);
    EXPECT_FLOAT_EQ(result.GetY(), -4.0f);
    EXPECT_FLOAT_EQ(result.GetZ(), -6.0f);
    EXPECT_FLOAT_EQ(result.GetW(), 1.0f);
}

TEST_F(NMTupleTest, NegateOperator)
{
    // Given
    NMTuple tuple(1.0f, -2.0f, 3.0f, -4.0f);

    // When
    NMTuple result = -tuple;

    // Then
    EXPECT_FLOAT_EQ(result.GetX(), -1.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 2.0f);
    EXPECT_FLOAT_EQ(result.GetZ(), -3.0f);
    EXPECT_FLOAT_EQ(result.GetW(), 4.0f);
}

TEST_F(NMTupleTest, MultiplicationOperator_Scalar)
{
    // Given
    NMTuple tuple(1.0f, -2.0f, 3.0f, -4.0f);

    // When
    NMTuple result = tuple * 3.5f;

    // Then
    EXPECT_FLOAT_EQ(result.GetX(), 3.5f);
    EXPECT_FLOAT_EQ(result.GetY(), -7.0f);
    EXPECT_FLOAT_EQ(result.GetZ(), 10.5f);
    EXPECT_FLOAT_EQ(result.GetW(), -14.0f);
}

TEST_F(NMTupleTest, MultiplicationOperator_Fraction)
{
    // Given
    NMTuple tuple(1.0f, -2.0f, 3.0f, -4.0f);

    // When
    NMTuple result = tuple * 0.5f;

    // Then
    EXPECT_FLOAT_EQ(result.GetX(), 0.5f);
    EXPECT_FLOAT_EQ(result.GetY(), -1.0f);
    EXPECT_FLOAT_EQ(result.GetZ(), 1.5f);
    EXPECT_FLOAT_EQ(result.GetW(), -2.0f);
}

TEST_F(NMTupleTest, DivisionOperator_Scalar)
{
    // Given
    NMTuple tuple(1.0f, -2.0f, 3.0f, -4.0f);

    // When
    NMTuple result = tuple / 2.0f;

    // Then
    EXPECT_FLOAT_EQ(result.GetX(), 0.5f);
    EXPECT_FLOAT_EQ(result.GetY(), -1.0f);
    EXPECT_FLOAT_EQ(result.GetZ(), 1.5f);
    EXPECT_FLOAT_EQ(result.GetW(), -2.0f);
}

TEST_F(NMTupleTest, StreamInsertionOperator)
{
    // Given
    NMTuple tuple(4.3f, -4.2f, 3.0f, 1.0f);

    // When
    std::stringstream stream;
    stream << tuple;

    // Then
    EXPECT_EQ(stream.str(), "(4.30, -4.20, 3.00, 1.00)");
}

TEST_F(NMTupleTest, StreamInsertionOperator_LimitedPrecision)
{
    // Given
    NMTuple tuple(4.0f / 3.0f, 5.0f / 3.0f, -2.0f, 1.0f);

    // When
    std::stringstream stream;
    stream << std::setprecision(2) << tuple;

    // Then
    EXPECT_EQ(stream.str(), "(1.33, 1.67, -2.00, 1.00)");
}

TEST_F(NMTupleTest, StreamInsertionOperator_Infinity)
{
    // Given
    NMTuple tuple(-3.0f, std::numeric_limits<float>::infinity() * -1, std::numeric_limits<float>::infinity(), 1.0f);

    // When
    std::stringstream stream;
    stream << tuple;

    // Then
    EXPECT_EQ(stream.str(), "(-3.00, -inf, inf, 1.00)");
}

TEST_F(NMTupleTest, StreamInsertionOperator_NaN)
{
    // Given
    NMTuple tuple(-3.0f, std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::signaling_NaN(), 1.0f);

    // When
    std::stringstream stream;
    stream << tuple;

    // Then
    EXPECT_EQ(stream.str(), "(-3.00, nan, nan, 1.00)");
}

#pragma endregion

#pragma region Cast Tests

TEST_F(NMTupleTest, Cast_Vector)
{
    // Given
    NMTuple tuple(4.3f, -4.2f, 3.1f, 0.0f);

    // When
    NMVector vector = tuple;

    // Then
    EXPECT_FLOAT_EQ(vector.GetX(), 4.3f);
    EXPECT_FLOAT_EQ(vector.GetY(), -4.2f);
    EXPECT_FLOAT_EQ(vector.GetZ(), 3.1f);
}

TEST_F(NMTupleTest, Cast_Vector_AsPoint)
{
    // Given
    NMTuple tuple(4.3f, -4.2f, 3.1f, 1.0f);

    // When
    NMVector point = tuple;

    // Then
    EXPECT_FLOAT_EQ(point.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(point.GetY(), 0.0f);
    EXPECT_FLOAT_EQ(point.GetZ(), 0.0f);
}

TEST_F(NMTupleTest, Cast_Point)
{
    // Given
    NMTuple tuple(4.3f, -4.2f, 3.1f, 1.0f);

    // When
    NMPoint point = tuple;

    // Then
    EXPECT_FLOAT_EQ(point.GetX(), 4.3f);
    EXPECT_FLOAT_EQ(point.GetY(), -4.2f);
    EXPECT_FLOAT_EQ(point.GetZ(), 3.1f);
}

TEST_F(NMTupleTest, Cast_Point_AsVector)
{
    // Given
    NMTuple tuple(4.3f, -4.2f, 3.1f, 0.0f);

    // When
    NMPoint point = tuple;

    // Then
    EXPECT_FLOAT_EQ(point.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(point.GetY(), 0.0f);
    EXPECT_FLOAT_EQ(point.GetZ(), 0.0f);
}

#pragma endregion

TEST_F(NMTupleTest, IsVector_Vector)
{
    // Given
    NMTuple tuple(4.3f, -4.2f, 3.1f, 0.0f);

    // When
    bool isVector = tuple.IsVector();

    // Then
    EXPECT_TRUE(isVector);
}

TEST_F(NMTupleTest, IsVector_Point)
{
    // Given
    NMTuple tuple(4.3f, -4.2f, 3.1f, 1.0f);

    // When
    bool isVector = tuple.IsVector();

    // Then
    EXPECT_FALSE(isVector);
}

TEST_F(NMTupleTest, IsPoint_Point)
{
    // Given
    NMTuple tuple(4.3f, -4.2f, 3.1f, 1.0f);

    // When
    bool isPoint = tuple.IsPoint();

    // Then
    EXPECT_TRUE(isPoint);
}

TEST_F(NMTupleTest, IsPoint_Vector)
{
    // Given
    NMTuple tuple(4.3f, -4.2f, 3.1f, 0.0f);

    // When
    bool isPoint = tuple.IsPoint();

    // Then
    EXPECT_FALSE(isPoint);
}

TEST_F(NMTupleTest, SquaredMagnitude)
{
    // Given
    NMTuple tuple1(1.0f, 0.0f, 0.0f, 0.0f);
    NMTuple tuple2(0.0f, 1.0f, 0.0f, 0.0f);
    NMTuple tuple3(0.0f, 0.0f, 1.0f, 0.0f);
    NMTuple tuple4(1.0f, 2.0f, 3.0f, 0.0f);
    NMTuple tuple5(-1.0f, -2.0f, -3.0f, 0.0f);

    // Then
    EXPECT_FLOAT_EQ(tuple1.SquaredMagnitude(), 1.0f);
    EXPECT_FLOAT_EQ(tuple2.SquaredMagnitude(), 1.0f);
    EXPECT_FLOAT_EQ(tuple3.SquaredMagnitude(), 1.0f);
    EXPECT_FLOAT_EQ(tuple4.SquaredMagnitude(), 14.0f);
    EXPECT_FLOAT_EQ(tuple5.SquaredMagnitude(), 14.0f);
}

TEST_F(NMTupleTest, Magnitude)
{
    // Given
    NMTuple tuple1(1.0f, 0.0f, 0.0f, 0.0f);
    NMTuple tuple2(0.0f, 1.0f, 0.0f, 0.0f);
    NMTuple tuple3(0.0f, 0.0f, 1.0f, 0.0f);
    NMTuple tuple4(1.0f, 2.0f, 3.0f, 0.0f);
    NMTuple tuple5(-1.0f, -2.0f, -3.0f, 0.0f);

    // Then
    EXPECT_FLOAT_EQ(tuple1.Magnitude(), 1.0f);
    EXPECT_FLOAT_EQ(tuple2.Magnitude(), 1.0f);
    EXPECT_FLOAT_EQ(tuple3.Magnitude(), 1.0f);
    EXPECT_FLOAT_EQ(tuple4.Magnitude(), std::sqrt(14.0f));
    EXPECT_FLOAT_EQ(tuple5.Magnitude(), std::sqrt(14.0f));
}

TEST_F(NMTupleTest, Normalized)
{
    // Given
    NMTuple tuple1(4.0f, 0.0f, 0.0f, 0.0f);
    NMTuple tuple2(1.0f, 2.0f, 3.0f, 0.0f);

    // When
    NMTuple normalized1 = tuple1.Normalized();
    NMTuple normalized2 = tuple2.Normalized();

    // Then
    EXPECT_FLOAT_EQ(normalized1.GetX(), 1.0f);
    EXPECT_FLOAT_EQ(normalized1.GetY(), 0.0f);
    EXPECT_FLOAT_EQ(normalized1.GetZ(), 0.0f);
    EXPECT_FLOAT_EQ(normalized1.GetW(), 0.0f);

    EXPECT_FLOAT_EQ(normalized2.GetX(), 1.0f / std::sqrt(14.0f));
    EXPECT_FLOAT_EQ(normalized2.GetY(), 2.0f / std::sqrt(14.0f));
    EXPECT_FLOAT_EQ(normalized2.GetZ(), 3.0f / std::sqrt(14.0f));
    EXPECT_FLOAT_EQ(normalized2.GetW(), 0.0f);
}
