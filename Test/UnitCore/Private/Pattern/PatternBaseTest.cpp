#include <gtest/gtest.h>

#include "NMCore/Pattern/PatternBase.hpp"
#include "NMCore/Primitive/Sphere.hpp"

class NMTestPattern : public NMPatternBase
{
public:

    NMTestPattern(const NMMatrix& transform = NMMatrix::Identity4x4()) : NMPatternBase(transform) {}

    virtual NMColor ColorAt(const NMPoint& point) const override
    {
        return NMColor(point.GetX(), point.GetY(), point.GetZ());
    }

};

class NMPatternBaseTest : public ::testing::Test
{
protected:

    NMColor black = NMColor(0.0f, 0.0f, 0.0f);
    NMColor white = NMColor(1.0f, 1.0f, 1.0f);

};

// Scenario: The default pattern transformation
//   Given pattern ← test_pattern()
//   Then pattern.transform = identity_matrix
TEST_F(NMPatternBaseTest, DefaultPatternTransformation)
{
    // Given
    NMTestPattern pattern = NMTestPattern();

    // Then
    EXPECT_EQ(pattern.GetTransform(), NMMatrix::Identity4x4());
}

// Scenario: Construct a pattern with an object transformation
//   Given pattern ← test_pattern(translation(2, 2, 2))
//   Then pattern.transform = translation(2, 2, 2)
TEST_F(NMPatternBaseTest, ConstructAPatternWithAnObjectTransformation)
{
    // Given
    NMTestPattern pattern = NMTestPattern(NMMatrix::Translation(2.0f, 2.0f, 2.0f));

    // Then
    EXPECT_EQ(pattern.GetTransform(), NMMatrix::Translation(2.0f, 2.0f, 2.0f));
}

// Scenario: Assigning a transformation
//   Given pattern ← test_pattern()
//     And set_transform(pattern, translation(1, 2, 3))
//   When set_pattern_transform(pattern, translation(1, 2, 3))
//   Then pattern.transform = translation(1, 2, 3)
TEST_F(NMPatternBaseTest, AssigningATransformation)
{
    // Given
    NMTestPattern pattern = NMTestPattern();

    // When
    pattern.SetTransform(NMMatrix::Translation(1.0f, 2.0f, 3.0f));

    // Then
    EXPECT_EQ(pattern.GetTransform(), NMMatrix::Translation(1.0f, 2.0f, 3.0f));
}

// Scenario: A pattern with an object transformation
//   Given shape ← sphere()
//     And set_transform(shape, scaling(2, 2, 2))
//     And pattern ← test_pattern()
//   When c ← pattern_at_shape(pattern, shape, point(2, 3, 4))
//   Then c = color(1, 1.5, 2)
TEST_F(NMPatternBaseTest, APatternWithAnObjectTransformation)
{
    // Given
    NMSphere shape = NMSphere();
    shape.SetTransform(NMMatrix::Scaling(2.0f, 2.0f, 2.0f));
    NMTestPattern pattern = NMTestPattern();

    // When
    NMColor c = pattern.ColorAtShapePoint(shape, NMPoint(2.0f, 3.0f, 4.0f));

    // Then
    EXPECT_EQ(c, NMColor(1.0f, 1.5f, 2.0f));
}

// Scenario: A pattern with a pattern transformation
//   Given shape ← sphere()
//     And pattern ← test_pattern(scaling(2, 2, 2))
//   When c ← pattern_at_shape(pattern, shape, point(2, 3, 4))
//   Then c = color(1, 1.5, 2)
TEST_F(NMPatternBaseTest, APatternWithAPatternTransformation)
{
    // Given
    NMSphere shape = NMSphere();
    NMTestPattern pattern = NMTestPattern(NMMatrix::Scaling(2.0f, 2.0f, 2.0f));

    // When
    NMColor c = pattern.ColorAtShapePoint(shape, NMPoint(2.0f, 3.0f, 4.0f));

    // Then
    EXPECT_EQ(c, NMColor(1.0f, 1.5f, 2.0f));
}

// Scenario: A pattern with both an object and a pattern transformation
//   Given shape ← sphere()
//     And set_transform(shape, scaling(2, 2, 2))
//     And pattern ← test_pattern(translation(0.5, 1, 1.5))
//   When c ← pattern_at_shape(pattern, shape, point(2.5, 3, 3.5))
//   Then c = color(0.75, 0.5, 0.25)
TEST_F(NMPatternBaseTest, APatternWithBothAnObjectAndAPatternTransformation)
{
    // Given
    NMSphere shape = NMSphere();
    shape.SetTransform(NMMatrix::Scaling(2.0f, 2.0f, 2.0f));
    NMTestPattern pattern = NMTestPattern(NMMatrix::Translation(0.5f, 1.0f, 1.5f));

    // When
    NMColor c = pattern.ColorAtShapePoint(shape, NMPoint(2.5f, 3.0f, 3.5f));

    // Then
    EXPECT_EQ(c, NMColor(0.75f, 0.5f, 0.25f));
}
