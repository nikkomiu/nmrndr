#include "MathTest.hpp"

#include "Math.hpp"

TEST_F(NMMathTest, FloatEquals)
{
    // Then
    EXPECT_TRUE(nmmath::FloatEquals(0.0f, 0.0f));
    EXPECT_TRUE(nmmath::FloatEquals(0.0f, 0.0000001f));
    EXPECT_TRUE(nmmath::FloatEquals(0.0000001f, 0.0f));
    EXPECT_FALSE(nmmath::FloatEquals(0.0f, 0.1f));
    EXPECT_FALSE(nmmath::FloatEquals(0.1f, 0.0f));
}
