#include <gtest/gtest.h>

#include "Primitive/Sphere.hpp"
#include "RT/Intersection.hpp"

class IntersectionTest : public ::testing::Test
{
};

TEST_F(IntersectionTest, IntersectionCreation)
{
    // Given
    NMSphere sphere = NMSphere();
    SNMIntersection intersection = SNMIntersection(3.5f, &sphere);

    // Then
    EXPECT_EQ(intersection.t, 3.5f);
    EXPECT_EQ(intersection.object, (void*)&sphere);
}
