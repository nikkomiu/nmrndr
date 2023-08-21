#include <gtest/gtest.h>

#include "NMM/Point.hpp"
#include "NMM/Vector.hpp"
#include "Primitive/Sphere.hpp"

class NMSphereTest : public ::testing::Test
{
};

TEST_F(NMSphereTest, SphereCreation_Default)
{
    // Given
    NMSphere sphere;

    // Then
    EXPECT_EQ(sphere.GetRadius(), 1.0f);
    EXPECT_EQ(sphere.GetOrigin(), NMPoint(0.0f, 0.0f, 0.0f));
}

// Scenario: A ray intersects a sphere at two points
TEST_F(NMSphereTest, SphereIntersect_TwoPoints)
{
    // Given
    NMRay ray = NMRay(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));
    NMSphere sphere;

    // When
    std::vector<float> t = sphere.Intersect(ray);

    // Then
    EXPECT_EQ(t.size(), 2);
    EXPECT_EQ(t[0], 4.0f);
    EXPECT_EQ(t[1], 6.0f);
}

// Scenario: A ray intersects a sphere at a tangent
TEST_F(NMSphereTest, SphereIntersect_Tangent)
{
    // Given
    NMRay ray = NMRay(NMPoint(0.0f, 1.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));
    NMSphere sphere;

    // When
    std::vector<float> t = sphere.Intersect(ray);

    // Then
    EXPECT_EQ(t.size(), 2);
    EXPECT_EQ(t[0], 5.0f);
    EXPECT_EQ(t[1], 5.0f);
}

// Scenario: A ray misses a sphere
TEST_F(NMSphereTest, SphereIntersect_Miss)
{
    // Given
    NMRay ray = NMRay(NMPoint(0.0f, 2.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));
    NMSphere sphere;

    // When
    std::vector<float> t = sphere.Intersect(ray);

    // Then
    EXPECT_EQ(t.size(), 0);
}

// Scenario: A ray originates inside a sphere
TEST_F(NMSphereTest, SphereIntersect_Inside)
{
    // Given
    NMRay ray = NMRay(NMPoint(0.0f, 0.0f, 0.0f), NMVector(0.0f, 0.0f, 1.0f));
    NMSphere sphere;

    // When
    std::vector<float> t = sphere.Intersect(ray);

    // Then
    EXPECT_EQ(t.size(), 2);
    EXPECT_EQ(t[0], -1.0f);
    EXPECT_EQ(t[1], 1.0f);
}

// Scenario: A sphere is behind a ray
TEST_F(NMSphereTest, SphereIntersect_Behind)
{
    // Given
    NMRay ray = NMRay(NMPoint(0.0f, 0.0f, 5.0f), NMVector(0.0f, 0.0f, 1.0f));
    NMSphere sphere;

    // When
    std::vector<float> t = sphere.Intersect(ray);

    // Then
    EXPECT_EQ(t.size(), 2);
    EXPECT_EQ(t[0], -6.0f);
    EXPECT_EQ(t[1], -4.0f);
}

// Scenario: A sphere's default transformation
TEST_F(NMSphereTest, SphereTransformation_Default)
{
    // Given
    NMSphere sphere;

    // Then
    EXPECT_EQ(sphere.GetTransform(), NMMatrix::Identity4x4());
}

// Scenario: Changing a sphere's transformation
TEST_F(NMSphereTest, SphereTransformation_Change)
{
    // Given
    NMSphere sphere;
    NMMatrix transform = NMMatrix::Translation(2.0f, 3.0f, 4.0f);

    // When
    sphere.SetTransform(transform);

    // Then
    EXPECT_EQ(sphere.GetTransform(), transform);
}

// Scenario: Intersecting a scaled sphere with a ray
TEST_F(NMSphereTest, SphereIntersect_Scaled)
{
    // Given
    NMRay ray = NMRay(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));
    NMSphere sphere;
    sphere.SetTransform(NMMatrix::Scaling(2.0f, 2.0f, 2.0f));

    // When
    std::vector<float> t = sphere.Intersect(ray);

    // Then
    EXPECT_EQ(t.size(), 2);
    EXPECT_EQ(t[0], 3.0f);
    EXPECT_EQ(t[1], 7.0f);
}

// Scenario: Intersecting a translated sphere with a ray
TEST_F(NMSphereTest, SphereIntersect_Translated)
{
    // Given
    NMRay ray = NMRay(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));
    NMSphere sphere;
    sphere.SetTransform(NMMatrix::Translation(5.0f, 0.0f, 0.0f));

    // When
    std::vector<float> t = sphere.Intersect(ray);

    // Then
    EXPECT_EQ(t.size(), 0);
}

// Scenario: The normal on a sphere at a point on the x axis
TEST_F(NMSphereTest, SphereNormal_XAxis)
{
    // Given
    NMSphere sphere;

    // When
    NMVector normal = sphere.NormalAt(NMPoint(1.0f, 0.0f, 0.0f));

    // Then
    EXPECT_EQ(normal, NMVector(1.0f, 0.0f, 0.0f));
}

// Scenario: The normal on a sphere at a point on the y axis
TEST_F(NMSphereTest, SphereNormal_YAxis)
{
    // Given
    NMSphere sphere;

    // When
    NMVector normal = sphere.NormalAt(NMPoint(0.0f, 1.0f, 0.0f));

    // Then
    EXPECT_EQ(normal, NMVector(0.0f, 1.0f, 0.0f));
}

// Scenario: The normal on a sphere at a point on the z axis
TEST_F(NMSphereTest, SphereNormal_ZAxis)
{
    // Given
    NMSphere sphere;

    // When
    NMVector normal = sphere.NormalAt(NMPoint(0.0f, 0.0f, 1.0f));

    // Then
    EXPECT_EQ(normal, NMVector(0.0f, 0.0f, 1.0f));
}

// Scenario: The normal on a sphere at a nonaxial point
TEST_F(NMSphereTest, SphereNormal_NonAxial)
{
    // Given
    NMSphere sphere;

    // When
    NMVector normal = sphere.NormalAt(NMPoint(sqrt(3.0f) / 3.0f, sqrt(3.0f) / 3.0f, sqrt(3.0f) / 3.0f));

    // Then
    EXPECT_EQ(normal, NMVector(sqrt(3.0f) / 3.0f, sqrt(3.0f) / 3.0f, sqrt(3.0f) / 3.0f));
}

// Scenario: The normal is a normalized vector
TEST_F(NMSphereTest, SphereNormal_Normalized)
{
    // Given
    NMSphere sphere;

    // When
    NMVector normal = sphere.NormalAt(NMPoint(sqrt(3.0f) / 3.0f, sqrt(3.0f) / 3.0f, sqrt(3.0f) / 3.0f));

    // Then
    EXPECT_EQ(normal, normal.Normalized());
}

// Scenario: Computing the normal on a translated sphere
TEST_F(NMSphereTest, SphereNormal_Translated)
{
    // Given
    NMSphere sphere;
    sphere.SetTransform(NMMatrix::Translation(0.0f, 1.0f, 0.0f));

    // When
    NMVector normal = sphere.NormalAt(NMPoint(0.0f, 1.70711f, -0.70711f));

    // Then
    EXPECT_EQ(normal, NMVector(0.0f, 0.707107f, -0.707107f));
}

// Scenario: Computing the normal on a transformed sphere
TEST_F(NMSphereTest, SphereNormal_Transformed)
{
    // Given
    NMSphere sphere;
    sphere.SetTransform(NMMatrix::Scaling(1.0f, 0.5f, 1.0f) * NMMatrix::RotationZ(M_PI / 5.0f));

    // When
    NMVector normal = sphere.NormalAt(NMPoint(0.0f, sqrt(2.0f) / 2.0f, -sqrt(2.0f) / 2.0f));

    // Then
    EXPECT_EQ(normal, NMVector(0.0f, 0.970143f, -0.242536f));
}
