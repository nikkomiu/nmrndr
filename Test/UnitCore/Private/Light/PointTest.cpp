#include <gtest/gtest.h>

#include "Light/Point.hpp"

class NMPointLightTest : public ::testing::Test
{
};

// Scenario: A point light has a position and intensity
TEST_F(NMPointLightTest, Creation)
{
    // Given
    NMPoint position(0, 0, 0);
    NMColor intensity(1, 1, 1);

    // When
    NMPointLight light(position, intensity);

    // Then
    ASSERT_EQ(light.GetPosition(), position);
    ASSERT_EQ(light.GetColor(), intensity);
}
