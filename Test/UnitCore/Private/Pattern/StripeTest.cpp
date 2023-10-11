#include <gtest/gtest.h>

#include "NMCore/Pattern/Stripe.hpp"
#include "NMCore/Primitive/Sphere.hpp"

class NMStripePatternTest : public ::testing::Test
{
protected:

    NMColor black = NMColor(0.0f, 0.0f, 0.0f);
    NMColor white = NMColor(1.0f, 1.0f, 1.0f);

};

// Scenario: Creating a stripe pattern
TEST_F(NMStripePatternTest, CreateStripePattern)
{
    // Given
    NMStripePattern pattern(white, black);

    // Then
    EXPECT_EQ(pattern.GetColorA(), white);
    EXPECT_EQ(pattern.GetColorB(), black);
}

// Scenario: A stripe pattern is constant in y
TEST_F(NMStripePatternTest, StripePatternConstantY)
{
    // Given
    NMStripePattern pattern(white, black);

    // Then
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 0.0f, 0.0f)), white);
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 1.0f, 0.0f)), white);
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 2.0f, 0.0f)), white);
}

// Scenario: A stripe pattern is constant in z
TEST_F(NMStripePatternTest, StripePatternConstantZ)
{
    // Given
    NMStripePattern pattern(white, black);

    // Then
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 0.0f, 0.0f)), white);
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 0.0f, 1.0f)), white);
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 0.0f, 2.0f)), white);
}

// Scenario: A stripe pattern alternates in x
TEST_F(NMStripePatternTest, StripePatternAlternatesX)
{
    // Given
    NMStripePattern pattern(white, black);

    // Then
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 0.0f, 0.0f)), white);
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.9f, 0.0f, 0.0f)), white);
    EXPECT_EQ(pattern.ColorAt(NMPoint(1.0f, 0.0f, 0.0f)), black);
    EXPECT_EQ(pattern.ColorAt(NMPoint(-0.1f, 0.0f, 0.0f)), black);
    EXPECT_EQ(pattern.ColorAt(NMPoint(-1.0f, 0.0f, 0.0f)), black);
    EXPECT_EQ(pattern.ColorAt(NMPoint(-1.1f, 0.0f, 0.0f)), white);
}
