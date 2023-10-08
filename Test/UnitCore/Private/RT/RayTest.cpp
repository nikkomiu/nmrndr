#include <gtest/gtest.h>

#include "NMM/Point.hpp"
#include "NMM/Vector.hpp"
#include "NMCore/RT/Ray.hpp"
#include "NMCore/Primitive/Sphere.hpp"

class NMRayTest : public ::testing::Test
{
};

// Scenario: Creating a default ray
TEST_F(NMRayTest, RayCreation_Default)
{
    // Given
    NMRay ray = NMRay();

    // Then
    EXPECT_EQ(ray.GetOrigin(), NMPoint(0.0f, 0.0f, 0.0f));
    EXPECT_EQ(ray.GetDirection(), NMVector(0.0f, 0.0f, 0.0f));
}

// Scenario: Creating and querying a ray
TEST_F(NMRayTest, RayCreation)
{
    // Given
    NMRay ray = NMRay(NMPoint(1.0f, 2.0f, 3.0f), NMVector(4.0f, 5.0f, 6.0f));

    // Then
    EXPECT_EQ(ray.GetOrigin(), NMPoint(1.0f, 2.0f, 3.0f));
    EXPECT_EQ(ray.GetDirection(), NMVector(4.0f, 5.0f, 6.0f));
}

// Scenario: Computing a point from a distance
TEST_F(NMRayTest, RayPosition)
{
    // Given
    NMRay ray = NMRay(NMPoint(2.0f, 3.0f, 4.0f), NMVector(1.0f, 0.0f, 0.0f));

    // Then
    EXPECT_EQ(ray.Position(0.0f), NMPoint(2.0f, 3.0f, 4.0f));
    EXPECT_EQ(ray.Position(1.0f), NMPoint(3.0f, 3.0f, 4.0f));
    EXPECT_EQ(ray.Position(-1.0f), NMPoint(1.0f, 3.0f, 4.0f));
    EXPECT_EQ(ray.Position(2.5f), NMPoint(4.5f, 3.0f, 4.0f));
}

// Scenario: Translating a ray
TEST_F(NMRayTest, RayTranslation)
{
    // Given
    NMRay ray = NMRay(NMPoint(1.0f, 2.0f, 3.0f), NMVector(0.0f, 1.0f, 0.0f));
    NMMatrix transform = NMMatrix::Translation(3.0f, 4.0f, 5.0f);

    // When
    NMRay transformedRay = ray.Transformed(transform);

    // Then
    EXPECT_NE(&ray, &transformedRay);
    EXPECT_EQ(transformedRay.GetOrigin(), NMPoint(4.0f, 6.0f, 8.0f));
    EXPECT_EQ(transformedRay.GetDirection(), NMVector(0.0f, 1.0f, 0.0f));
}

// Scenario: Scaling a ray
TEST_F(NMRayTest, RayScaling)
{
    // Given
    NMRay ray = NMRay(NMPoint(1.0f, 2.0f, 3.0f), NMVector(0.0f, 1.0f, 0.0f));
    NMMatrix transform = NMMatrix::Scaling(2.0f, 3.0f, 4.0f);

    // When
    NMRay transformedRay = ray.Transformed(transform);

    // Then
    EXPECT_NE(&ray, &transformedRay);
    EXPECT_EQ(transformedRay.GetOrigin(), NMPoint(2.0f, 6.0f, 12.0f));
    EXPECT_EQ(transformedRay.GetDirection(), NMVector(0.0f, 3.0f, 0.0f));
}
