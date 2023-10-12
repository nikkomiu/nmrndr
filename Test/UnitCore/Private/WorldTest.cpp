#include <gtest/gtest.h>

#include "NMCore/World.hpp"
#include "NMCore/RT/Intersection.hpp"

class NMWorldTest : public ::testing::Test
{
};

// Scenario: Create a world
TEST_F(NMWorldTest, CreateWorld)
{
    // Given
    NMWorld world;

    // Then
    ASSERT_EQ(world.GetPointLightCount(), 0);
    ASSERT_EQ(world.GetObjectCount(), 0);
}

// Scenario: The default world
TEST_F(NMWorldTest, DefaultWorld)
{
    // Given
    NMWorld world = NMWorld::Default();

    // Then
    ASSERT_EQ(world.GetPointLightCount(), 1);
    ASSERT_EQ(world.GetObjectCount(), 2);

    NMPointLight pointLight = world.GetPointLight(0);
    ASSERT_EQ(pointLight.GetPosition(), NMPoint(-10.0f, 10.0f, -10.0f));
    ASSERT_EQ(pointLight.GetColor(), NMColor(1.0f, 1.0f, 1.0f));

    std::shared_ptr<NMPrimitiveBase> sphere = world.GetObject(0);
    ASSERT_EQ(sphere->GetTransform(), NMMatrix::Identity4x4());
    ASSERT_EQ(sphere->GetMaterial(), NMMaterial(NMColor(0.8f, 1.0f, 0.6f), 0.1f, 0.7f, 0.2f, 200.0f));

    sphere = world.GetObject(1);
    ASSERT_EQ(sphere->GetTransform(), NMMatrix::Scaling(0.5f, 0.5f, 0.5f));
    ASSERT_EQ(sphere->GetMaterial(), NMMaterial());
}

TEST_F(NMWorldTest, SetLight)
{
    // Given
    NMWorld world;

    // When
    world.AddLight(NMPointLight(NMPoint(0.0f, 0.0f, 1.0f), NMColor(1.0f, 0.5f, 1.0f)));
    world.SetLight(0, NMPointLight(NMPoint(0.0f, 0.0f, 0.0f), NMColor(1.0f, 1.0f, 1.0f)));

    // Then
    ASSERT_EQ(world.GetPointLightCount(), 1);
    ASSERT_EQ(world.GetPointLight(0).GetPosition(), NMPoint(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(world.GetPointLight(0).GetColor(), NMColor(1.0f, 1.0f, 1.0f));
}

TEST_F(NMWorldTest, SetLight_OutOfBounds)
{
    // Given
    NMWorld world;

    // When
    world.SetLight(2, NMPointLight(NMPoint(0.0f, 0.0f, 0.0f), NMColor(1.0f, 1.0f, 1.0f)));

    // Then
    ASSERT_EQ(world.GetPointLightCount(), 0);
}

// Scenario: Intersect a world with a ray
TEST_F(NMWorldTest, IntersectWorld)
{
    // Given
    NMWorld world = NMWorld::Default();

    // When
    SNMIntersectionList intersections = world.Intersect(NMRay(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f)));

    // Then
    ASSERT_EQ(intersections.Size(), 4);
    ASSERT_FLOAT_EQ(intersections[0].t, 4.0f);
    ASSERT_FLOAT_EQ(intersections[1].t, 4.5f);
    ASSERT_FLOAT_EQ(intersections[2].t, 5.5f);
    ASSERT_FLOAT_EQ(intersections[3].t, 6.0f);
}

// Scenario: Shading an intersection
TEST_F(NMWorldTest, ShadingIntersection)
{
    // Given
    NMWorld world = NMWorld::Default();
    NMRay ray(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));
    SNMIntersectionList intersections = world.Intersect(ray);

    // When
    NMColor color = world.ShadeHit(SNMIntersectionState(intersections[0], ray));

    // Then
    ASSERT_EQ(color, NMColor(0.380661f, 0.475827f, 0.285496f));
}

// Scenario: Shading an intersection from the inside
TEST_F(NMWorldTest, ShadingIntersectionInside)
{
    // Given
    NMWorld world = NMWorld::Default();
    world.SetLight(0, NMPointLight(NMPoint(0.0f, 0.25f, 0.0f), NMColor(1.0f, 1.0f, 1.0f)));
    NMRay ray(NMPoint(0.0f, 0.0f, 0.0f), NMVector(0.0f, 0.0f, 1.0f));
    std::shared_ptr<NMPrimitiveBase> shape = world.GetObject(1);
    SNMIntersection intersection(0.5f, shape.get());

    // When
    NMColor color = world.ShadeHit(SNMIntersectionState(intersection, ray));

    // Then
    ASSERT_EQ(color, NMColor(0.1f, 0.1f, 0.1f));
}

// Scenario: ShadeHit() is given an intersection in shadow
TEST_F(NMWorldTest, ShadingIntersectionShadow)
{
    // Given
    NMWorld world;
    world.AddLight(NMPointLight(NMPoint(0.0f, 0.0f, -10.0f), NMColor(1.0f, 1.0f, 1.0f)));

    std::shared_ptr<NMPrimitiveBase> s1 = std::make_shared<NMSphere>();
    s1->SetTransform(NMMatrix::Translation(0.0f, 0.0f, 10.0f));
    world.AddObject(s1);

    std::shared_ptr<NMPrimitiveBase> s2 = std::make_shared<NMSphere>();
    world.AddObject(s2);

    NMRay ray(NMPoint(0.0f, 0.0f, 5.0f), NMVector(0.0f, 0.0f, 1.0f));
    SNMIntersection intersection(4.0f, s2.get());

    // When
    NMColor color = world.ShadeHit(SNMIntersectionState(intersection, ray));

    // Then
    ASSERT_EQ(color, NMColor(0.1f, 0.1f, 0.1f));
}

// Scenario: The color when a ray misses
TEST_F(NMWorldTest, ColorMiss)
{
    // Given
    NMWorld world = NMWorld::Default();
    NMRay ray(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 1.0f, 0.0f));

    // When
    NMColor color = world.ColorAt(ray);

    // Then
    ASSERT_EQ(color, NMColor(0.0f, 0.0f, 0.0f));
}

// Scenario: The color when a ray hits
TEST_F(NMWorldTest, ColorHit)
{
    // Given
    NMWorld world = NMWorld::Default();
    NMRay ray(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));

    // When
    NMColor color = world.ColorAt(ray);

    // Then
    ASSERT_EQ(color, NMColor(0.380661f, 0.475827f, 0.285496f));
}

// Scenario: The color with an intersection behind the ray
TEST_F(NMWorldTest, ColorBehind)
{
    // Given
    NMWorld world = NMWorld::Default();
    std::shared_ptr<NMPrimitiveBase> outer = world.GetObject(0);
    outer->SetMaterial(NMMaterial(NMColor(0.8f, 1.0f, 0.6f), 1.0f, 0.7f, 0.2f, 200.0f));
    std::shared_ptr<NMPrimitiveBase> inner = world.GetObject(1);
    inner->SetMaterial(NMMaterial(NMColor(0.8f, 1.0f, 0.6f), 1.0f, 0.7f, 0.2f, 200.0f));
    NMRay ray(NMPoint(0.0f, 0.0f, 0.75f), NMVector(0.0f, 0.0f, -1.0f));

    // When
    NMColor color = world.ColorAt(ray);

    // Then
    ASSERT_EQ(color, inner->GetMaterial().GetColor());
}

// Scenario: There is no shadow when nothing is collinear with point and light
TEST_F(NMWorldTest, NoShadow)
{
    // Given
    NMWorld world = NMWorld::Default();
    NMPoint point = NMPoint(0.0f, 10.0f, 0.0f);

    // When
    bool isInShadow = world.IsShadowed(point);

    // Then
    ASSERT_FALSE(isInShadow);
}

// Scenario: The shadow when an object is between the point and the light
TEST_F(NMWorldTest, Shadow)
{
    // Given
    NMWorld world = NMWorld::Default();
    NMPoint point = NMPoint(10.0f, -10.0f, 10.0f);

    // When
    bool isInShadow = world.IsShadowed(point);

    // Then
    ASSERT_TRUE(isInShadow);
}

// Scenario: There is no shadow when an object is behind the light
TEST_F(NMWorldTest, NoShadowBehindLight)
{
    // Given
    NMWorld world = NMWorld::Default();
    NMPoint point = NMPoint(-20.0f, 20.0f, -20.0f);

    // When
    bool isInShadow = world.IsShadowed(point);

    // Then
    ASSERT_FALSE(isInShadow);
}

// Scenario: There is no shadow when an object is behind the point
TEST_F(NMWorldTest, NoShadowBehindPoint)
{
    // Given
    NMWorld world = NMWorld::Default();
    NMPoint point = NMPoint(-2.0f, 2.0f, -2.0f);

    // When
    bool isInShadow = world.IsShadowed(point);

    // Then
    ASSERT_FALSE(isInShadow);
}
