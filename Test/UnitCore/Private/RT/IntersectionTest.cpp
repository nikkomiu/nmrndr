#include <gtest/gtest.h>

#include "NMCore/Primitive/Sphere.hpp"
#include "NMCore/RT/Intersection.hpp"

class IntersectionTest : public ::testing::Test
{
};

TEST_F(IntersectionTest, IntersectionCreation)
{
    // Given
    NMSphere* sphere = new NMSphere();
    SNMIntersection intersection = SNMIntersection(3.5f, sphere);

    // Then
    EXPECT_EQ(intersection.t, 3.5f);
    EXPECT_TRUE(intersection.object == sphere);
}
