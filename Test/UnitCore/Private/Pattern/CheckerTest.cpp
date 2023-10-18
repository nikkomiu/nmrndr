#include <gtest/gtest.h>

#include "NMCore/Pattern/Checker.hpp"

class NMCheckerPatternTest : public testing::Test
{
protected:

    NMColor black = NMColor(0.0f, 0.0f, 0.0f);
    NMColor white = NMColor(1.0f, 1.0f, 1.0f);
};

TEST_F(NMCheckerPatternTest, CheckerPatternCreation)
{
    // Given
    NMColor black = NMColor(0.0f, 0.0f, 0.0f);
    NMColor white = NMColor(1.0f, 1.0f, 1.0f);

    // When
    NMCheckerPattern pattern(white, black);

    // Then
    EXPECT_EQ(pattern.GetColorA(), white);
    EXPECT_EQ(pattern.GetColorB(), black);
}

// Scenario: Checkers should repeat in x
TEST_F(NMCheckerPatternTest, CheckerPatternRepeatX)
{
    // Given
    NMCheckerPattern pattern(white, black);

    // Then
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 0.0f, 0.0f)), white);
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.99f, 0.0f, 0.0f)), white);
    EXPECT_EQ(pattern.ColorAt(NMPoint(1.01f, 0.0f, 0.0f)), black);
}

// Scenario: Checkers should repeat in y
TEST_F(NMCheckerPatternTest, CheckerPatternRepeatY)
{
    // Given
    NMCheckerPattern pattern(white, black);

    // Then
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 0.0f, 0.0f)), white);
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 0.99f, 0.0f)), white);
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 1.01f, 0.0f)), black);
}

// Scenario: Checkers should repeat in z
TEST_F(NMCheckerPatternTest, CheckerPatternRepeatZ)
{
    // Given
    NMCheckerPattern pattern(white, black);

    // Then
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 0.0f, 0.0f)), white);
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 0.0f, 0.99f)), white);
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 0.0f, 1.01f)), black);
}
