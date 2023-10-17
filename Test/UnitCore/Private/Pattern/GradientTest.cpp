#include <gtest/gtest.h>

#include "NMCore/Pattern/Gradient.hpp"

class NMGradientPatternTest : public ::testing::Test
{
protected:

    NMColor black = NMColor(0.0f, 0.0f, 0.0f);
    NMColor white = NMColor(1.0f, 1.0f, 1.0f);

};

TEST_F(NMGradientPatternTest, GradientPatternCreation)
{
    // Given
    NMColor black = NMColor(0.0f, 0.0f, 0.0f);
    NMColor white = NMColor(1.0f, 1.0f, 1.0f);

    // When
    NMGradientPattern pattern(white, black);

    // Then
    EXPECT_EQ(pattern.GetColorA(), white);
    EXPECT_EQ(pattern.GetColorB(), black);
}

// Scenario: A gradient linearly interpolates between colors
TEST_F(NMGradientPatternTest, GradientPatternLinearlyInterpolates)
{
    // Given
    NMGradientPattern pattern(white, black);

    // Then
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 0.0f, 0.0f)), white);
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.25f, 0.0f, 0.0f)), NMColor(0.75f, 0.75f, 0.75f));
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.5f, 0.0f, 0.0f)), NMColor(0.5f, 0.5f, 0.5f));
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.75f, 0.0f, 0.0f)), NMColor(0.25f, 0.25f, 0.25f));
}
