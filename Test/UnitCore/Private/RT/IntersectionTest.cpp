#include <gtest/gtest.h>

#include "NMCore/Primitive/Sphere.hpp"
#include "NMCore/RT/Intersection.hpp"

class SNMIntersectionTest : public ::testing::Test
{
};

TEST_F(SNMIntersectionTest, IntersectionCreation)
{
    // Given
    NMSphere* sphere = new NMSphere();
    SNMIntersection intersection = SNMIntersection(3.5f, sphere);

    // Then
    EXPECT_EQ(intersection.t, 3.5f);
    EXPECT_TRUE(intersection.object == sphere);
}

TEST_F(SNMIntersectionTest, EqualityOperator)
{
    // Given
    NMSphere* sphere = new NMSphere();
    SNMIntersection intersection1 = SNMIntersection(3.5f, sphere);
    SNMIntersection intersection2 = SNMIntersection(3.5f, sphere);

    // Then
    EXPECT_TRUE(intersection1 == intersection2);
}

TEST_F(SNMIntersectionTest, EqualityOperator_DifferentT)
{
    // Given
    NMSphere* sphere = new NMSphere();
    SNMIntersection intersection1 = SNMIntersection(3.5f, sphere);
    SNMIntersection intersection2 = SNMIntersection(3.6f, sphere);

    // Then
    EXPECT_FALSE(intersection1 == intersection2);
}

TEST_F(SNMIntersectionTest, EqualityOperator_DifferentObject)
{
    // Given
    NMSphere* sphere1 = new NMSphere();
    NMSphere* sphere2 = new NMSphere();
    sphere2->SetTransform(NMMatrix::Translation(0.0f, 1.0f, 0.0f));
    SNMIntersection intersection1 = SNMIntersection(3.5f, sphere1);
    SNMIntersection intersection2 = SNMIntersection(3.5f, sphere2);

    // Then
    EXPECT_FALSE(intersection1 == intersection2);
}
