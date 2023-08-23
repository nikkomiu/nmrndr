#include <gtest/gtest.h>

#include "Primitive/Plane.hpp"

class NMPlaneTest : public ::testing::Test
{
};

// Scenario: The normal of a plance is constant
TEST_F(NMPlaneTest, Normal_IsConstant)
{
    // Given
    NMPlane plane;

    // When
    NMVector normal1 = plane.LocalNormalAt(NMPoint(0.0f, 0.0f, 0.0f));
    NMVector normal2 = plane.LocalNormalAt(NMPoint(10.0f, 0.0f, 0.0f));
    NMVector normal3 = plane.LocalNormalAt(NMPoint(-5.0f, 0.0f, 0.0f));

    // Then
    EXPECT_EQ(normal1, NMVector(0.0f, 1.0f, 0.0f));
    EXPECT_EQ(normal2, NMVector(0.0f, 1.0f, 0.0f));
    EXPECT_EQ(normal3, NMVector(0.0f, 1.0f, 0.0f));
}

// Scenario: Intersect with a ray parallel to the plane
TEST_F(NMPlaneTest, Intersect_ParallelRay)
{
    // Given
    NMPlane plane;
    NMRay ray(NMPoint(0.0f, 10.0f, 0.0f), NMVector(0.0f, 0.0f, 1.0f));

    // When
    std::vector<SNMIntersection> intersections = plane.LocalIntersect(ray);

    // Then
    EXPECT_EQ(intersections.size(), 0);
}

// Scenario: Intersect with a coplanar ray
TEST_F(NMPlaneTest, Intersect_CoplanarRay)
{
    // Given
    NMPlane plane;
    NMRay ray(NMPoint(0.0f, 0.0f, 0.0f), NMVector(0.0f, 0.0f, 1.0f));

    // When
    std::vector<SNMIntersection> intersections = plane.LocalIntersect(ray);

    // Then
    EXPECT_EQ(intersections.size(), 0);
}

// Scenario: A ray intersecting a plane from above
TEST_F(NMPlaneTest, Intersect_FromAbove)
{
    // Given
    NMPlane plane;
    NMRay ray(NMPoint(0.0f, 1.0f, 0.0f), NMVector(0.0f, -1.0f, 0.0f));

    // When
    std::vector<SNMIntersection> intersections = plane.LocalIntersect(ray);

    // Then
    EXPECT_EQ(intersections.size(), 1);
    EXPECT_EQ(intersections[0].t, 1.0f);
    EXPECT_EQ(intersections[0].object, &plane);
}

// Scenario: A ray intersecting a plane from below
TEST_F(NMPlaneTest, Intersect_FromBelow)
{
    // Given
    NMPlane plane;
    NMRay ray(NMPoint(0.0f, -1.0f, 0.0f), NMVector(0.0f, 1.0f, 0.0f));

    // When
    std::vector<SNMIntersection> intersections = plane.LocalIntersect(ray);

    // Then
    EXPECT_EQ(intersections.size(), 1);
    EXPECT_EQ(intersections[0].t, 1.0f);
    EXPECT_EQ(intersections[0].object, &plane);
}
