#include <gtest/gtest.h>

#include "RT/IIntersectionObject.hpp"

class IntersectionObjectTest : public ::testing::Test
{
};

TEST_F(IntersectionObjectTest, PureAbstractClass)
{
    // Then
    EXPECT_EQ(sizeof(INMIntersectionObject), 8);
}
