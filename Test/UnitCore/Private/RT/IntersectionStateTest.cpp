#include <gtest/gtest.h>

#include "NMCore/RT/IntersectionState.hpp"
#include "NMCore/World.hpp"
#include "NMCore/Primitive/Plane.hpp"

class SNMIntersectionStateTest : public ::testing::Test
{
protected:

    NMWorld defaultWorld = NMWorld::Default();
};

// Scenario: Precomputing the state of an intersection
TEST_F(SNMIntersectionStateTest, PrecomputeState)
{
    // Given
    NMRay ray(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));
    SNMIntersectionList intersections = defaultWorld.Intersect(ray);

    // When
    SNMIntersectionState state = SNMIntersectionState(intersections[0], ray);

    // Then
    std::shared_ptr<NMPrimitiveBase> sphere = defaultWorld.GetObject(0);
    const NMPrimitiveBase* stateObject = state.object;
    ASSERT_TRUE(stateObject == sphere.get());
    ASSERT_EQ(state.point, NMPoint(0.0f, 0.0f, -1.0f));
    ASSERT_EQ(state.eyeVector, NMVector(0.0f, 0.0f, -1.0f));
    ASSERT_EQ(state.normalVector, NMVector(0.0f, 0.0f, -1.0f));
}

// Scenario: The hit, when an intersection occurs on the outside
TEST_F(SNMIntersectionStateTest, HitOutside)
{
    // Given
    NMRay ray(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));
    SNMIntersectionList intersections = defaultWorld.Intersect(ray);

    // When
    SNMIntersectionState state = SNMIntersectionState(intersections[0], ray);

    // Then
    ASSERT_FALSE(state.isInside);
}

// Scenario: The hit, when an intersection occurs on the inside
TEST_F(SNMIntersectionStateTest, HitInside)
{
    // Given
    NMRay ray(NMPoint(0.0f, 0.0f, 0.0f), NMVector(0.0f, 0.0f, 1.0f));
    SNMIntersectionList intersections = defaultWorld.Intersect(ray);

    // When
    SNMIntersectionState state = SNMIntersectionState(intersections[1], ray);

    // Then
    ASSERT_EQ(state.point, NMPoint(0.0f, 0.0f, 1.0f));
    ASSERT_EQ(state.eyeVector, NMVector(0.0f, 0.0f, -1.0f));
    ASSERT_TRUE(state.isInside);
    ASSERT_EQ(state.normalVector, NMVector(0.0f, 0.0f, -1.0f));
}

// Scenario: The hit should offset the point
TEST_F(SNMIntersectionStateTest, HitOffset)
{
    // Given
    NMRay ray(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));
    NMSphere sphere;
    sphere.SetTransform(NMMatrix::Translation(0.0f, 0.0f, 1.0f));
    SNMIntersection intersection(5.0f, &sphere);

    // When
    SNMIntersectionState state = SNMIntersectionState(intersection, ray);

    // Then
    ASSERT_TRUE(state.overPoint.GetZ() < -nmmath::rayEpsilon / 2.0f);
    ASSERT_TRUE(state.point.GetZ() > state.overPoint.GetZ());
}

// Scenario: Precomputing the reflection vector
TEST_F(SNMIntersectionStateTest, PrecomputeReflectionVector)
{
    // Given
    NMPlane plane = NMPlane();
    NMRay ray(NMPoint(0.0f, 1.0f, -1.0f), NMVector(0.0f, -nmmath::sqrt2Over2, nmmath::sqrt2Over2));
    SNMIntersection intersection(std::sqrt(2.0f), &plane);

    // When
    SNMIntersectionState state = SNMIntersectionState(intersection, ray);

    // Then
    ASSERT_EQ(state.reflectVector, NMVector(0.0f, nmmath::sqrt2Over2, nmmath::sqrt2Over2));
}

TEST_F(SNMIntersectionStateTest, StreamingInsertionOperator)
{
    // Given
    NMRay ray(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));
    SNMIntersectionList intersections = defaultWorld.Intersect(ray);
    SNMIntersectionState state = SNMIntersectionState(intersections[0], ray);

    // When
    std::stringstream stream;
    stream << state;

    // Then
    std::stringstream expected;
    expected << "IntersectionState(" << std::endl;
    expected << "\tt: 4" << std::endl;
    expected << "\tobject: " << state.object << std::endl;
    expected << "\tpoint: (0.00, 0.00, -1.00)" << std::endl;
    expected << "\toverPoint: (0.00, 0.00, -1.00)" << std::endl;
    expected << "\teyeVector: (-0.00, -0.00, -1.00)" << std::endl;
    expected << "\tnormalVector: (0.00, 0.00, -1.00)" << std::endl;
    expected << "\treflectVector: (0.00, 0.00, -1.00)" << std::endl;
    expected << "\tisInside: 0" << std::endl;
    expected << ")" << std::endl;
    ASSERT_EQ(stream.str(), expected.str());
}
