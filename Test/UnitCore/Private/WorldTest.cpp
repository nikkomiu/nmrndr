#include <gtest/gtest.h>

#include "NMCore/Primitive/Plane.hpp"
#include "NMCore/RT/Intersection.hpp"
#include "NMCore/World.hpp"

class NMWorldTest : public ::testing::Test
{
protected:

    NMWorld defaultWorld;

    void SetUp() override
    {
    defaultWorld = NMWorld::Default();
    }
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
    // Then
    ASSERT_EQ(defaultWorld.GetPointLightCount(), 1);
    ASSERT_EQ(defaultWorld.GetObjectCount(), 2);

    NMPointLight pointLight = defaultWorld.GetPointLight(0);
    ASSERT_EQ(pointLight.GetPosition(), NMPoint(-10.0f, 10.0f, -10.0f));
    ASSERT_EQ(pointLight.GetColor(), NMColor(1.0f, 1.0f, 1.0f));

    std::shared_ptr<NMPrimitiveBase> sphere = defaultWorld.GetObject(0);
    ASSERT_EQ(sphere->GetTransform(), NMMatrix::Identity4x4());
    ASSERT_EQ(sphere->GetMaterial(), NMMaterial(NMColor(0.8f, 1.0f, 0.6f), 0.1f, 0.7f, 0.2f, 200.0f));

    sphere = defaultWorld.GetObject(1);
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
    // When
    SNMIntersectionList intersections = defaultWorld.Intersect(NMRay(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f)));

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
    NMRay ray(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));
    SNMIntersectionList intersections = defaultWorld.Intersect(ray);

    // When
    NMColor color = defaultWorld.ShadeHit(SNMIntersectionState(intersections[0], ray), 8);

    // Then
    ASSERT_EQ(color, NMColor(0.380661f, 0.475827f, 0.285496f));
}

// Scenario: Shading an intersection from the inside
TEST_F(NMWorldTest, ShadingIntersectionInside)
{
    // Given
    defaultWorld.SetLight(0, NMPointLight(NMPoint(0.0f, 0.25f, 0.0f), NMColor(1.0f, 1.0f, 1.0f)));
    NMRay ray(NMPoint(0.0f, 0.0f, 0.0f), NMVector(0.0f, 0.0f, 1.0f));
    std::shared_ptr<NMPrimitiveBase> shape = defaultWorld.GetObject(1);
    SNMIntersection intersection(0.5f, shape.get());

    // When
    NMColor color = defaultWorld.ShadeHit(SNMIntersectionState(intersection, ray), 8);

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
    NMColor color = world.ShadeHit(SNMIntersectionState(intersection, ray), 8);

    // Then
    ASSERT_EQ(color, NMColor(0.1f, 0.1f, 0.1f));
}

// Scenario: The color when a ray misses
TEST_F(NMWorldTest, ColorMiss)
{
    // Given
    NMRay ray(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 1.0f, 0.0f));

    // When
    NMColor color = defaultWorld.ColorAt(ray);

    // Then
    ASSERT_EQ(color, NMColor(0.0f, 0.0f, 0.0f));
}

// Scenario: The color when a ray hits
TEST_F(NMWorldTest, ColorHit)
{
    // Given
    NMRay ray(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));

    // When
    NMColor color = defaultWorld.ColorAt(ray);

    // Then
    ASSERT_EQ(color, NMColor(0.380661f, 0.475827f, 0.285496f));
}

// Scenario: The color with an intersection behind the ray
TEST_F(NMWorldTest, ColorBehind)
{
    // Given
    std::shared_ptr<NMPrimitiveBase> outer = defaultWorld.GetObject(0);
    outer->SetMaterial(NMMaterial(NMColor(0.8f, 1.0f, 0.6f), 1.0f, 0.7f, 0.2f, 200.0f));
    std::shared_ptr<NMPrimitiveBase> inner = defaultWorld.GetObject(1);
    inner->SetMaterial(NMMaterial(NMColor(0.8f, 1.0f, 0.6f), 1.0f, 0.7f, 0.2f, 200.0f));
    NMRay ray(NMPoint(0.0f, 0.0f, 0.75f), NMVector(0.0f, 0.0f, -1.0f));

    // When
    NMColor color = defaultWorld.ColorAt(ray);

    // Then
    ASSERT_EQ(color, inner->GetMaterial().GetColor());
}

// Scenario: There is no shadow when nothing is collinear with point and light
TEST_F(NMWorldTest, NoShadow)
{
    // Given
    NMPoint point = NMPoint(0.0f, 10.0f, 0.0f);

    // When
    bool isInShadow = defaultWorld.IsShadowed(point);

    // Then
    ASSERT_FALSE(isInShadow);
}

// Scenario: The shadow when an object is between the point and the light
TEST_F(NMWorldTest, Shadow)
{
    // Given
    NMPoint point = NMPoint(10.0f, -10.0f, 10.0f);

    // When
    bool isInShadow = defaultWorld.IsShadowed(point);

    // Then
    ASSERT_TRUE(isInShadow);
}

// Scenario: There is no shadow when an object is behind the light
TEST_F(NMWorldTest, NoShadowBehindLight)
{
    // Given
    NMPoint point = NMPoint(-20.0f, 20.0f, -20.0f);

    // When
    bool isInShadow = defaultWorld.IsShadowed(point);

    // Then
    ASSERT_FALSE(isInShadow);
}

// Scenario: There is no shadow when an object is behind the point
TEST_F(NMWorldTest, NoShadowBehindPoint)
{
    // Given
    NMPoint point = NMPoint(-2.0f, 2.0f, -2.0f);

    // When
    bool isInShadow = defaultWorld.IsShadowed(point);

    // Then
    ASSERT_FALSE(isInShadow);
}

// Scenario: The reflected color for a nonreflective material
TEST_F(NMWorldTest, ReflectedColor_Nonreflective)
{
    // Given
    std::shared_ptr<NMPrimitiveBase> shape = defaultWorld.GetObject(1);
    shape->SetMaterial(NMMaterial(NMColor(0.8f, 1.0f, 0.6f), 1.0f, 0.7f, 0.0f, 200.0f));
    NMRay ray(NMPoint(0.0f, 0.0f, 0.0f), NMVector(0.0f, 0.0f, 1.0f));
    SNMIntersection intersection(1.0f, shape.get());

    // When
    NMColor color = defaultWorld.ReflectedColor(SNMIntersectionState(intersection, ray), 99);

    // Then
    ASSERT_EQ(color, NMColor(0.0f, 0.0f, 0.0f));
}

// Scenario: The reflected color for a reflective material
TEST_F(NMWorldTest, ReflectedColor_Reflective)
{
    // Given
    std::shared_ptr<NMPrimitiveBase> shape = std::make_shared<NMPlane>();
    NMMaterial shapeMat = NMMaterial();
    shapeMat.SetReflective(0.5f);
    shape->SetMaterial(shapeMat);
    shape->SetTransform(NMMatrix::Translation(0.0f, -1.0f, 0.0f));
    defaultWorld.AddObject(shape);

    NMRay ray(NMPoint(0.0f, 0.0f, -3.0f), NMVector(0.0f, -nmmath::sqrt2Over2, nmmath::sqrt2Over2));
    SNMIntersection intersection(std::sqrt(2.0f), shape.get());

    // When
    SNMIntersectionState state(intersection, ray);
    NMColor color = defaultWorld.ReflectedColor(state, 99);

    // Then
    ASSERT_EQ(color, NMColor(0.191192f, 0.238991f, 0.143394f));
}

// Scenario: ShadeHit with a reflective material
TEST_F(NMWorldTest, ShadeHit_WithReflectiveMaterial)
{
    // Given
    std::shared_ptr<NMPrimitiveBase> shape = std::make_shared<NMPlane>();
    NMMaterial shapeMat = NMMaterial();
    shapeMat.SetReflective(0.5f);
    shape->SetMaterial(shapeMat);
    shape->SetTransform(NMMatrix::Translation(0.0f, -1.0f, 0.0f));
    defaultWorld.AddObject(shape);

    NMRay ray(NMPoint(0.0f, 0.0f, -3.0f), NMVector(0.0f, -nmmath::sqrt2Over2, nmmath::sqrt2Over2));
    SNMIntersection intersection(std::sqrt(2.0f), shape.get());

    // When
    SNMIntersectionState state(intersection, ray);
    NMColor color = defaultWorld.ShadeHit(state, 8);

    // Then
    ASSERT_EQ(color, NMColor(0.877618f, 0.925416f, 0.829819f));
}

// Scenario: ColorAt with mutually reflective surfaces
TEST_F(NMWorldTest, ColorAt_MutuallyReflectiveSurfaces)
{
    // Given
    NMWorld world;
    world.AddLight(NMPointLight(NMPoint(0.0f, 0.0f, 0.0f), NMColor(1.0f, 1.0f, 1.0f)));

    std::shared_ptr<NMPrimitiveBase> lower = std::make_shared<NMPlane>();
    NMMaterial lowerMat = NMMaterial();
    lowerMat.SetReflective(1.0f);
    lower->SetMaterial(lowerMat);
    lower->SetTransform(NMMatrix::Translation(0.0f, -1.0f, 0.0f));
    world.AddObject(lower);

    std::shared_ptr<NMPrimitiveBase> upper = std::make_shared<NMPlane>();
    NMMaterial upperMat = NMMaterial();
    upperMat.SetReflective(1.0f);
    upper->SetMaterial(upperMat);
    // TODO: the normal is backwards...this seems to be causing the overpoint to
    // be facing the wrong direction for the upper plane...fix this to show the "nomral"...
    upper->SetTransform(NMMatrix::Translation(0.0f, 1.0f, 0.0f) * NMMatrix::RotationX(nmmath::pi));
    world.AddObject(upper);

    NMRay ray(NMPoint(0.0f, 0.0f, 0.0f), NMVector(0.0f, 1.0f, 0.0f));

    // When
    NMColor color = world.ColorAt(ray);

    // Then
    ASSERT_EQ(color.GetClamped(), NMColor(1.0f, 1.0f, 1.0f));
}

// Scenario: The reflected color at the maximum recursive depth
TEST_F(NMWorldTest, ReflectedColor_MaxRecursiveDepth)
{
    // Given
    std::shared_ptr<NMPrimitiveBase> shape = std::make_shared<NMPlane>();
    NMMaterial shapeMat = NMMaterial();
    shapeMat.SetReflective(0.5f);
    shape->SetMaterial(shapeMat);
    shape->SetTransform(NMMatrix::Translation(0.0f, -1.0f, 0.0f));
    defaultWorld.AddObject(shape);

    NMRay ray(NMPoint(0.0f, 0.0f, -3.0f), NMVector(0.0f, -nmmath::sqrt2Over2, nmmath::sqrt2Over2));
    SNMIntersection intersection(std::sqrt(2.0f), shape.get());

    // When
    SNMIntersectionState state(intersection, ray);
    NMColor color = defaultWorld.ReflectedColor(state, 0);

    // Then
    ASSERT_EQ(color, NMColor(0.0f, 0.0f, 0.0f));
}
