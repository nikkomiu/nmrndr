#include <gtest/gtest.h>

#include "World.hpp"
#include "RT/Intersection.hpp"

class WorldTest : public ::testing::Test
{
};

// Scenario: Create a world
TEST_F(WorldTest, CreateWorld)
{
    // Given
    NMWorld world;

    // Then
    ASSERT_EQ(world.GetPointLightCount(), 0);
    ASSERT_EQ(world.GetObjectCount(), 0);
}

// Scenario: The default world
TEST_F(WorldTest, DefaultWorld)
{
    // Given
    NMWorld world = NMWorld::Default();

    // Then
    ASSERT_EQ(world.GetPointLightCount(), 1);
    ASSERT_EQ(world.GetObjectCount(), 2);

    NMPointLight pointLight = world.GetPointLight(0);
    ASSERT_EQ(pointLight.GetPosition(), NMPoint(-10.0f, 10.0f, -10.0f));
    ASSERT_EQ(pointLight.GetColor(), NMColor(1.0f, 1.0f, 1.0f));

    std::shared_ptr<INMIntersectionObject> sphere = world.GetObject(0);
    ASSERT_EQ(sphere->GetTransform(), NMMatrix::Identity4x4());
    ASSERT_EQ(sphere->GetMaterial(), NMMaterial(NMColor(0.8f, 1.0f, 0.6f), 0.1f, 0.7f, 0.2f, 200.0f));

    sphere = world.GetObject(1);
    ASSERT_EQ(sphere->GetTransform(), NMMatrix::Scaling(0.5f, 0.5f, 0.5f));
    ASSERT_EQ(sphere->GetMaterial(), NMMaterial());
}

// Scenario: Intersect a world with a ray
TEST_F(WorldTest, IntersectWorld)
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

// Scenario: Precomputing the state of an intersection
TEST_F(WorldTest, PrecomputeState)
{
    // Given
    NMWorld world = NMWorld::Default();
    NMRay ray(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));
    SNMIntersectionList intersections = world.Intersect(ray);

    // When
    SNMIntersectionState state = world.PrepareState(intersections[0], ray);

    // Then
    std::shared_ptr<INMIntersectionObject> sphere = world.GetObject(0);
    const INMIntersectionObject* stateObject = state.object;
    ASSERT_TRUE(stateObject == sphere.get());
    ASSERT_EQ(state.point, NMPoint(0.0f, 0.0f, -1.0f));
    ASSERT_EQ(state.eyeVector, NMVector(0.0f, 0.0f, -1.0f));
    ASSERT_EQ(state.normalVector, NMVector(0.0f, 0.0f, -1.0f));
}

// Scenario: The hit, when an intersection occurs on the outside
TEST_F(WorldTest, HitOutside)
{
    // Given
    NMWorld world = NMWorld::Default();
    NMRay ray(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));
    SNMIntersectionList intersections = world.Intersect(ray);

    // When
    SNMIntersectionState state = world.PrepareState(intersections[0], ray);

    // Then
    ASSERT_FALSE(state.isInside);
}

// Scenario: The hit, when an intersection occurs on the inside
TEST_F(WorldTest, HitInside)
{
    // Given
    NMWorld world = NMWorld::Default();
    NMRay ray(NMPoint(0.0f, 0.0f, 0.0f), NMVector(0.0f, 0.0f, 1.0f));
    SNMIntersectionList intersections = world.Intersect(ray);

    // When
    SNMIntersectionState state = world.PrepareState(intersections[1], ray);

    // Then
    ASSERT_EQ(state.point, NMPoint(0.0f, 0.0f, 1.0f));
    ASSERT_EQ(state.eyeVector, NMVector(0.0f, 0.0f, -1.0f));
    ASSERT_TRUE(state.isInside);
    ASSERT_EQ(state.normalVector, NMVector(0.0f, 0.0f, -1.0f));
}

// Scenario: Shading an intersection
TEST_F(WorldTest, ShadingIntersection)
{
    // Given
    NMWorld world = NMWorld::Default();
    NMRay ray(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));
    SNMIntersectionList intersections = world.Intersect(ray);

    // When
    SNMIntersectionState state = world.PrepareState(intersections[0], ray);
    NMColor color = world.ShadeHit(state);

    // Then
    ASSERT_EQ(color, NMColor(0.380661f, 0.475827f, 0.285496f));
}

// Scenario: Shading an intersection from the inside
TEST_F(WorldTest, ShadingIntersectionInside)
{
    // Given
    NMWorld world = NMWorld::Default();
    world.SetLight(0, NMPointLight(NMPoint(0.0f, 0.25f, 0.0f), NMColor(1.0f, 1.0f, 1.0f)));
    NMRay ray(NMPoint(0.0f, 0.0f, 0.0f), NMVector(0.0f, 0.0f, 1.0f));
    std::shared_ptr<INMIntersectionObject> shape = world.GetObject(1);
    SNMIntersection intersection(0.5f, shape.get());

    // When
    SNMIntersectionState state = world.PrepareState(intersection, ray);
    NMColor color = world.ShadeHit(state);

    // Then
    ASSERT_EQ(color, NMColor(0.904984f, 0.904984f, 0.904984f));
}

// Scenario: The color when a ray misses
TEST_F(WorldTest, ColorMiss)
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
TEST_F(WorldTest, ColorHit)
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
TEST_F(WorldTest, ColorBehind)
{
    // Given
    NMWorld world = NMWorld::Default();
    std::shared_ptr<INMIntersectionObject> outer = world.GetObject(0);
    outer->SetMaterial(NMMaterial(NMColor(0.8f, 1.0f, 0.6f), 1.0f, 0.7f, 0.2f, 200.0f));
    std::shared_ptr<INMIntersectionObject> inner = world.GetObject(1);
    inner->SetMaterial(NMMaterial(NMColor(0.8f, 1.0f, 0.6f), 1.0f, 0.7f, 0.2f, 200.0f));
    NMRay ray(NMPoint(0.0f, 0.0f, 0.75f), NMVector(0.0f, 0.0f, -1.0f));

    // When
    NMColor color = world.ColorAt(ray);

    // Then
    ASSERT_EQ(color, inner->GetMaterial().GetColor());
}
