#include <gtest/gtest.h>

#include "Math.hpp"

class NMMathTest : public ::testing::Test
{
};

TEST_F(NMMathTest, FloatEquals)
{
    // Then
    EXPECT_TRUE(nmmath::FloatEquals(0.0f, 0.0f));
    EXPECT_TRUE(nmmath::FloatEquals(0.0f, 0.0000001f));
    EXPECT_TRUE(nmmath::FloatEquals(0.0000001f, 0.0f));
    EXPECT_FALSE(nmmath::FloatEquals(0.0f, 0.1f));
    EXPECT_FALSE(nmmath::FloatEquals(0.1f, 0.0f));
}

TEST_F(NMMathTest, Clamp_Min)
{
    // Then
    EXPECT_EQ(nmmath::Clamp(-1, 0, 10), 0);
}

TEST_F(NMMathTest, Clamp_Max)
{
    // Then
    EXPECT_EQ(nmmath::Clamp(11, 0, 10), 10);
}

TEST_F(NMMathTest, Clamp_Middle)
{
    // Then
    EXPECT_EQ(nmmath::Clamp(5, 0, 10), 5);
}
