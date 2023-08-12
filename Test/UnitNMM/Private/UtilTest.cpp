#include <gtest/gtest.h>

#include "NMM/Util.hpp"

class NMUtilTest : public ::testing::Test
{
};

TEST_F(NMUtilTest, FloatEquals)
{
    // Then
    EXPECT_TRUE(nmmath::FloatEquals(0.0f, 0.0f));
    EXPECT_TRUE(nmmath::FloatEquals(0.0f, 0.0000001f));
    EXPECT_TRUE(nmmath::FloatEquals(0.0000001f, 0.0f));
    EXPECT_FALSE(nmmath::FloatEquals(0.0f, 0.1f));
    EXPECT_FALSE(nmmath::FloatEquals(0.1f, 0.0f));
}

TEST_F(NMUtilTest, Clamp_Min)
{
    // Then
    EXPECT_EQ(nmmath::Clamp(-1, 0, 10), 0);
}

TEST_F(NMUtilTest, Clamp_Max)
{
    // Then
    EXPECT_EQ(nmmath::Clamp(11, 0, 10), 10);
}

TEST_F(NMUtilTest, Clamp_Middle)
{
    // Then
    EXPECT_EQ(nmmath::Clamp(5, 0, 10), 5);
}
