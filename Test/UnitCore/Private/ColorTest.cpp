#include <gtest/gtest.h>

#include "NMCore/Color.hpp"

class NMColorTest : public ::testing::Test
{
};

TEST_F(NMColorTest, ColorCreation_Default)
{
    // Given
    NMColor color;

    // Then
    EXPECT_FLOAT_EQ(color.GetRed(), 0.0f);
    EXPECT_FLOAT_EQ(color.GetGreen(), 0.0f);
    EXPECT_FLOAT_EQ(color.GetBlue(), 0.0f);
}

TEST_F(NMColorTest, ColorCreation)
{
    // Given
    NMColor color(-0.5f, 0.4f, 1.7f);

    // Then
    EXPECT_FLOAT_EQ(color.GetRed(), -0.5f);
    EXPECT_FLOAT_EQ(color.GetGreen(), 0.4f);
    EXPECT_FLOAT_EQ(color.GetBlue(), 1.7f);
}

TEST_F(NMColorTest, ColorArrayOperator)
{
    // Given
    NMColor color(-0.5f, 0.4f, 1.7f);

    // Then
    EXPECT_EQ(color[0], -0.5f);
    EXPECT_EQ(color[1], 0.4f);
    EXPECT_EQ(color[2], 1.7f);
    EXPECT_EQ(color[3], 1.0f);
    EXPECT_EQ(color[4], 0.0f);
    EXPECT_EQ(color[5], 0.0f);
}

TEST_F(NMColorTest, Color_Clamped)
{
    // Given
    NMColor startColor = NMColor(0.5f, 0.5f, 0.5f);

    // When
    NMColor clampedColor = startColor.GetClamped();

    // Then
    EXPECT_EQ(clampedColor, NMColor(0.5f, 0.5f, 0.5f));
}

TEST_F(NMColorTest, Color_Clamped_Min)
{
    // Given
    NMColor startColor = NMColor(-0.5f, -0.5f, -0.5f);

    // When
    NMColor clampedColor = startColor.GetClamped();

    // Then
    EXPECT_EQ(clampedColor, NMColor(0.0f, 0.0f, 0.0f));
}

TEST_F(NMColorTest, Color_Clamped_Max)
{
    // Given
    NMColor startColor = NMColor(1000.5f, 1000.5f, 1000.5f);

    // When
    NMColor clampedColor = startColor.GetClamped();

    // Then
    EXPECT_EQ(clampedColor, NMColor(1.0f, 1.0f, 1.0f));
}

TEST_F(NMColorTest, GetClampedColor_Min)
{
    // Given
    NMColor color(-0.5f, -0.4f, -1.0f);

    // Then
    EXPECT_EQ(color.GetClampedRed(), 0);
    EXPECT_EQ(color.GetClampedGreen(), 0);
    EXPECT_EQ(color.GetClampedBlue(), 0);
}

TEST_F(NMColorTest, GetClampedColor_Max)
{
    // Given
    NMColor color(1.5f, 1.4f, 1.9f);

    // Then
    EXPECT_EQ(color.GetClampedRed(), 255);
    EXPECT_EQ(color.GetClampedGreen(), 255);
    EXPECT_EQ(color.GetClampedBlue(), 255);
}

TEST_F(NMColorTest, GetClampedColor_Middle)
{
    // Given
    NMColor color(0.5f, 0.4f, 1.0f);

    // Then
    EXPECT_EQ(color.GetClampedRed(), 127);
    EXPECT_EQ(color.GetClampedGreen(), 102);
    EXPECT_EQ(color.GetClampedBlue(), 255);
}

TEST_F(NMColorTest, ColorEquality)
{
    // Given
    NMColor color1(0.0f, 0.0f, 0.0f);
    NMColor color2(0.0f, 0.0f, 0.0f);

    // Then
    EXPECT_TRUE(color1 == color2);
}

TEST_F(NMColorTest, ColorEquality_RNotEqual)
{
    // Given
    NMColor color1(0.0f, 0.0f, 0.0f);
    NMColor color2(1.0f, 0.0f, 0.0f);

    // Then
    EXPECT_FALSE(color1 == color2);
}

TEST_F(NMColorTest, ColorEquality_GNotEqual)
{
    // Given
    NMColor color1(0.0f, 0.0f, 0.0f);
    NMColor color2(0.0f, 1.0f, 0.0f);

    // Then
    EXPECT_FALSE(color1 == color2);
}

TEST_F(NMColorTest, ColorEquality_BNotEqual)
{
    // Given
    NMColor color1(0.0f, 0.0f, 0.0f);
    NMColor color2(0.0f, 0.0f, 1.0f);

    // Then
    EXPECT_FALSE(color1 == color2);
}

TEST_F(NMColorTest, ColorAddition)
{
    // Given
    NMColor color1(0.9f, 0.6f, 0.75f);
    NMColor color2(0.7f, 0.1f, 0.25f);

    // When
    NMColor color3 = color1 + color2;

    // Then
    EXPECT_FLOAT_EQ(color3.GetRed(), 1.6f);
    EXPECT_FLOAT_EQ(color3.GetGreen(), 0.7f);
    EXPECT_FLOAT_EQ(color3.GetBlue(), 1.0f);
}

TEST_F(NMColorTest, ColorSubtraction)
{
    // Given
    NMColor color1(0.9f, 0.6f, 0.75f);
    NMColor color2(0.7f, 0.1f, 0.25f);

    // When
    NMColor color3 = color1 - color2;

    // Then
    EXPECT_FLOAT_EQ(color3.GetRed(), 0.2f);
    EXPECT_FLOAT_EQ(color3.GetGreen(), 0.5f);
    EXPECT_FLOAT_EQ(color3.GetBlue(), 0.5f);
}

TEST_F(NMColorTest, ColorMultiply_Scalar)
{
    // Given
    NMColor color1(0.2f, 0.3f, 0.4f);

    // When
    NMColor color2 = color1 * 2.0f;

    // Then
    EXPECT_FLOAT_EQ(color2.GetRed(), 0.4f);
    EXPECT_FLOAT_EQ(color2.GetGreen(), 0.6f);
    EXPECT_FLOAT_EQ(color2.GetBlue(), 0.8f);
}

TEST_F(NMColorTest, ColorMultiply)
{
    // Given
    NMColor color1(1.0f, 0.2f, 0.4f);
    NMColor color2(0.9f, 1.0f, 0.1f);

    // When
    NMColor color3 = color1 * color2;

    // Then
    EXPECT_FLOAT_EQ(color3.GetRed(), 0.9f);
    EXPECT_FLOAT_EQ(color3.GetGreen(), 0.2f);
    EXPECT_FLOAT_EQ(color3.GetBlue(), 0.04f);
}

TEST_F(NMColorTest, ColorAddAssign)
{
    // Given
    NMColor color1(0.9f, 0.6f, 0.75f);
    NMColor color2(0.7f, 0.1f, 0.25f);

    // When
    color1 += color2;

    // Then
    EXPECT_FLOAT_EQ(color1.GetRed(), 1.6f);
    EXPECT_FLOAT_EQ(color1.GetGreen(), 0.7f);
    EXPECT_FLOAT_EQ(color1.GetBlue(), 1.0f);
}

TEST_F(NMColorTest, ColorSubtractAssign)
{
    // Given
    NMColor color1(0.9f, 0.6f, 0.75f);
    NMColor color2(0.7f, 0.1f, 0.25f);

    // When
    color1 -= color2;

    // Then
    EXPECT_FLOAT_EQ(color1.GetRed(), 0.2f);
    EXPECT_FLOAT_EQ(color1.GetGreen(), 0.5f);
    EXPECT_FLOAT_EQ(color1.GetBlue(), 0.5f);
}

TEST_F(NMColorTest, ColorMultiplyAssign_Scalar)
{
    // Given
    NMColor color1(0.2f, 0.3f, 0.4f);

    // When
    color1 *= 2.0f;

    // Then
    EXPECT_FLOAT_EQ(color1.GetRed(), 0.4f);
    EXPECT_FLOAT_EQ(color1.GetGreen(), 0.6f);
    EXPECT_FLOAT_EQ(color1.GetBlue(), 0.8f);
}

TEST_F(NMColorTest, ColorMultiplyAssign)
{
    // Given
    NMColor color1(1.0f, 0.2f, 0.4f);
    NMColor color2(0.9f, 1.0f, 0.1f);

    // When
    color1 *= color2;

    // Then
    EXPECT_FLOAT_EQ(color1.GetRed(), 0.9f);
    EXPECT_FLOAT_EQ(color1.GetGreen(), 0.2f);
    EXPECT_FLOAT_EQ(color1.GetBlue(), 0.04f);
}

TEST_F(NMColorTest, ColorStreamInsertionOperator)
{
    // Given
    NMColor color(0.9f, 0.6f, 0.75f);

    // When
    std::stringstream ss;
    ss << color;

    // Then
    EXPECT_EQ(ss.str(), "rgb(230, 153, 191)");
}

TEST_F(NMColorTest, ColorStreamInsertionOperator_OutOfRange)
{
    // Given
    NMColor color(1.5f, -0.5f, 0.75f);

    // When
    std::stringstream ss;
    ss << color;

    // Then
    EXPECT_EQ(ss.str(), "rgb(382, -128, 191)");
}

TEST_F(NMColorTest, ColorStreamInsertionOperator_NaN)
{
    // Given
    NMColor color(std::numeric_limits<float>::quiet_NaN(), -0.5f, 0.75f);

    // When
    std::stringstream ss;
    ss << color;

    // Then
    EXPECT_EQ(ss.str(), "rgb(nan, -128, 191)");
}

TEST_F(NMColorTest, ColorStreamInsertionOperator_Infinity)
{
    // Given
    NMColor color(std::numeric_limits<float>::infinity(), -0.5f, std::numeric_limits<float>::infinity() * -1.0f);

    // When
    std::stringstream ss;
    ss << color;

    // Then
    EXPECT_EQ(ss.str(), "rgb(inf, -128, -inf)");
}
