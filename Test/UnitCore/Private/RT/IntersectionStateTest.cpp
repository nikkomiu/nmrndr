#include <gtest/gtest.h>

#include "NMCore/RT/IntersectionState.hpp"
#include "NMCore/World.hpp"
#include "NMCore/Primitive/Plane.hpp"

class SNMIntersectionStateTest : public testing::Test
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

// Refreaction Testing

struct SRefractionTestParams
{
public:

    uint32_t index;
    float n1;
    float n2;

    SRefractionTestParams(uint32_t index, float n1, float n2) : index(index), n1(n1), n2(n2) {}

    friend std::ostream& operator<<(std::ostream& os, const SRefractionTestParams& params)
    {
        os << "P(i:" << params.index << ", n1:" << params.n1 << " n2:" << params.n2 << ")";
        return os;
    }
};

class SNMIntersectionStateRefractionTest : public SNMIntersectionStateTest,
    public testing::WithParamInterface<SRefractionTestParams>
{
public:

    void SetUp() override
    {
        sphereA = NMSphere::GlassSphere();
        sphereA.SetTransform(NMMatrix::Scaling(2.0f, 2.0f, 2.0f));
        NMMaterial sphereAMaterial;
        sphereAMaterial.SetRefractiveIndex(1.5f);
        sphereA.SetMaterial(sphereAMaterial);

        sphereB = NMSphere::GlassSphere();
        sphereB.SetTransform(NMMatrix::Translation(0.0f, 0.0f, -0.25f));
        NMMaterial sphereBMaterial;
        sphereBMaterial.SetRefractiveIndex(2.0f);
        sphereB.SetMaterial(sphereBMaterial);

        sphereC = NMSphere::GlassSphere();
        sphereC.SetTransform(NMMatrix::Translation(0.0f, 0.0f, 0.25f));
        NMMaterial sphereCMaterial;
        sphereCMaterial.SetRefractiveIndex(2.5f);
        sphereC.SetMaterial(sphereCMaterial);

        ray = NMRay(NMPoint(0.0f, 0.0f, -4.0f), NMVector(0.0f, 0.0f, 1.0f));

        intersections = SNMIntersectionList({
            SNMIntersection(2.0f, &sphereA),
            SNMIntersection(2.75f, &sphereB),
            SNMIntersection(3.25f, &sphereC),
            SNMIntersection(4.75f, &sphereB),
            SNMIntersection(5.25f, &sphereC),
            SNMIntersection(6.0f, &sphereA)
        });
    }

protected:

    NMSphere sphereA;
    NMSphere sphereB;
    NMSphere sphereC;

    NMRay ray;

    SNMIntersectionList intersections;
};

// Scenario: Finding n1 and n2 at various intersections
TEST_P(SNMIntersectionStateRefractionTest, N1N2AtPoints)
{
    // Given
    const SRefractionTestParams& tt = GetParam();

    // When
    SNMIntersectionState state = SNMIntersectionState(intersections[tt.index], ray, intersections);

    // Then
    ASSERT_EQ(state.n1, tt.n1);
    ASSERT_EQ(state.n2, tt.n2);
}

INSTANTIATE_TEST_SUITE_P(SNMIntersectionState, SNMIntersectionStateRefractionTest, testing::Values(
    SRefractionTestParams(0, 1.0f, 1.5f),
    SRefractionTestParams(1, 1.5f, 2.0f),
    SRefractionTestParams(2, 2.0f, 2.5f),
    SRefractionTestParams(3, 2.5f, 2.5f),
    SRefractionTestParams(4, 2.5f, 1.5f),
    SRefractionTestParams(5, 1.5f, 1.0f)
));
