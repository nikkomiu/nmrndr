#include <gtest/gtest.h>

#include "NMCore/Pattern/Ring.hpp"

class NMRingPatternTest : public testing::Test
{
protected:

    NMColor black = NMColor(0.0f, 0.0f, 0.0f);
    NMColor white = NMColor(1.0f, 1.0f, 1.0f);
};

TEST_F(NMRingPatternTest, RingPatternCreation)
{
    // Given
    NMColor black = NMColor(0.0f, 0.0f, 0.0f);
    NMColor white = NMColor(1.0f, 1.0f, 1.0f);

    // When
    NMRingPattern pattern(white, black);

    // Then
    EXPECT_EQ(pattern.GetColorA(), white);
    EXPECT_EQ(pattern.GetColorB(), black);
}

// Scenario: A ring should extend in both x and z
TEST_F(NMRingPatternTest, RingPatternExtendsXZ)
{
    // Given
    NMRingPattern pattern(white, black);

    // Then
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 0.0f, 0.0f)), white);
    EXPECT_EQ(pattern.ColorAt(NMPoint(1.0f, 0.0f, 0.0f)), black);
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.0f, 0.0f, 1.0f)), black);
    EXPECT_EQ(pattern.ColorAt(NMPoint(0.708f, 0.0f, 0.708f)), black);
}
