#include <gtest/gtest.h>

#include "NMCore/Primitive/PrimitiveBase.hpp"

class NMTestShape : public NMPrimitiveBase
{
public:

    NMTestShape() = default;
    virtual ~NMTestShape() = default;

    mutable NMRay lastLocalIntersectRay;

protected:

    virtual std::vector<SNMIntersection> LocalIntersect(const NMRay& localRay) const override
    {
        lastLocalIntersectRay = localRay;
        return std::vector<SNMIntersection>();
    }
};

class NMPrimitiveBaseTest : public testing::Test
{
};

// Scenario: Equality of two shapes
TEST_F(NMPrimitiveBaseTest, PrimitiveBase_EqualityOperator)
{
    // Given
    NMTestShape shape1;
    NMTestShape shape2;

    // When
    bool result = shape1 == shape2;

    // Then
    EXPECT_TRUE(result);
}

// Scenario: Equality of two shapes with different transforms
TEST_F(NMPrimitiveBaseTest, PrimitiveBase_EqualityOperator_FailsWithTransform)
{
    // Given
    NMTestShape shape1;
    NMTestShape shape2;
    shape2.SetTransform(NMMatrix::Translation(0.0f, 1.0f, 0.0f));

    // When
    bool result = shape1 == shape2;

    // Then
    EXPECT_FALSE(result);
}

// Scenario: Equality of two shapes with different materials
TEST_F(NMPrimitiveBaseTest, PrimitiveBase_EqualityOperator_FailsWithMaterial)
{
    // Given
    NMTestShape shape1;
    NMTestShape shape2;
    NMMaterial material = NMMaterial();
    material.SetAmbient(1.0f);
    shape2.SetMaterial(material);

    // When
    bool result = shape1 == shape2;

    // Then
    EXPECT_FALSE(result);
}

TEST_F(NMPrimitiveBaseTest, PrimitiveBase_EqualityOperator_FailsWithDifferentOrigin)
{
    // Given
    NMTestShape shape1;
    NMTestShape shape2;
    shape2.SetOrigin(NMPoint(1.0f, 0.0f, 0.0f));

    // When
    bool result = shape1 == shape2;

    // Then
    EXPECT_FALSE(result);
}

// Scenario: The default transformation
TEST_F(NMPrimitiveBaseTest, PrimitiveBase_DefaultTransformation)
{
    // Given
    NMTestShape shape;

    // Then
    EXPECT_EQ(shape.GetTransform(), NMMatrix::Identity4x4());
}

// Scenario: Assigning a transformation
TEST_F(NMPrimitiveBaseTest, PrimitiveBase_AssigningTransformation)
{
    // Given
    NMTestShape shape;
    NMMatrix transform = NMMatrix::Translation(2.0f, 3.0f, 4.0f);

    // When
    shape.SetTransform(transform);

    // Then
    EXPECT_EQ(shape.GetTransform(), transform);
}

// Scenario: The default material
TEST_F(NMPrimitiveBaseTest, PrimitiveBase_DefaultMaterial)
{
    // Given
    NMTestShape shape;

    // Then
    EXPECT_EQ(shape.GetMaterial(), NMMaterial());
}

// Scenario: Assigning a material
TEST_F(NMPrimitiveBaseTest, PrimitiveBase_AssigningMaterial)
{
    // Given
    NMTestShape shape;
    NMMaterial material = NMMaterial();
    material.SetAmbient(1.0f);

    // When
    shape.SetMaterial(material);

    // Then
    EXPECT_EQ(shape.GetMaterial(), material);
}

// Scenario: Intersecting a scaled shape with a ray
TEST_F(NMPrimitiveBaseTest, PrimitiveBase_IntersectingScaledShape)
{
    // Given
    NMTestShape shape;
    shape.SetTransform(NMMatrix::Scaling(2.0f, 2.0f, 2.0f));
    NMRay ray = NMRay(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));

    // When
    shape.Intersect(ray);

    // Then
    EXPECT_EQ(shape.lastLocalIntersectRay.GetOrigin(), NMPoint(0.0f, 0.0f, -2.5f));
    EXPECT_EQ(shape.lastLocalIntersectRay.GetDirection(), NMVector(0.0f, 0.0f, 0.5f));
}

// Scenario: Intersecting a translated shape with a ray
TEST_F(NMPrimitiveBaseTest, PrimitiveBase_IntersectingTranslatedShape)
{
    // Given
    NMTestShape shape;
    shape.SetTransform(NMMatrix::Translation(5.0f, 0.0f, 0.0f));
    NMRay ray = NMRay(NMPoint(0.0f, 0.0f, -5.0f), NMVector(0.0f, 0.0f, 1.0f));

    // When
    shape.Intersect(ray);

    // Then
    EXPECT_EQ(shape.lastLocalIntersectRay.GetOrigin(), NMPoint(-5.0f, 0.0f, -5.0f));
    EXPECT_EQ(shape.lastLocalIntersectRay.GetDirection(), NMVector(0.0f, 0.0f, 1.0f));
}

// Scenario: Computing the normal on a translated shape
TEST_F(NMPrimitiveBaseTest, PrimitiveBase_ComputingNormalOnTranslatedShape)
{
    // Given
    NMTestShape shape;
    shape.SetTransform(NMMatrix::Translation(0.0f, 1.0f, 0.0f));

    // When
    NMVector normal = shape.NormalAt(NMPoint(0.0f, 1.70711f, -0.70711f));

    // Then
    EXPECT_EQ(normal, NMVector(0.0f, 0.707107f, -0.707107f));
}

// Scenario: Computing the normal on a transformed shape
TEST_F(NMPrimitiveBaseTest, PrimitiveBase_ComputingNormalOnTransformedShape)
{
    // Given
    NMTestShape shape;
    NMMatrix transform = NMMatrix::Scaling(1.0f, 0.5f, 1.0f) * NMMatrix::RotationZ(static_cast<float>(M_PI / 5.0f));
    shape.SetTransform(transform);

    // When
    NMVector normal = shape.NormalAt(NMPoint(0.0f, nmmath::sqrt2Over2, -nmmath::sqrt2Over2));

    // Then
    EXPECT_EQ(normal, NMVector(0.0f, 0.970143f, -0.242536f));
}
