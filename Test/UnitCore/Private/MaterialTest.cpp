#include <gtest/gtest.h>

#include "NMCore/Material.hpp"
#include "NMCore/Light/Point.hpp"
#include "NMCore/Pattern/Stripe.hpp"
#include "NMCore/Primitive/Sphere.hpp"
#include "NMM/Vector.hpp"

class NMMaterialTest : public ::testing::Test
{
};

// Scenario: The default material
TEST_F(NMMaterialTest, Creation_Default)
{
    // Given
    NMMaterial material;

    // Then
    ASSERT_EQ(material.GetColor(), NMColor(1, 1, 1));
    ASSERT_FLOAT_EQ(material.GetAmbient(), 0.1f);
    ASSERT_FLOAT_EQ(material.GetDiffuse(), 0.9f);
    ASSERT_FLOAT_EQ(material.GetSpecular(), 0.9f);
    ASSERT_FLOAT_EQ(material.GetShininess(), 200.0f);
}

// Scenario: A material can be created
TEST_F(NMMaterialTest, Creation)
{
    // Given
    NMColor color(1, 1, 1);
    float ambient = 0.1f;
    float diffuse = 0.9f;
    float specular = 0.9f;
    float shininess = 200.0f;

    // When
    NMMaterial material(color, ambient, diffuse, specular, shininess);

    // Then
    ASSERT_EQ(material.GetColor(), color);
    ASSERT_FLOAT_EQ(material.GetAmbient(), ambient);
    ASSERT_FLOAT_EQ(material.GetDiffuse(), diffuse);
    ASSERT_FLOAT_EQ(material.GetSpecular(), specular);
    ASSERT_FLOAT_EQ(material.GetShininess(), shininess);
}

TEST_F(NMMaterialTest, EqualityOperator)
{
    // Given
    NMMaterial material1(NMColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);
    NMMaterial material2(NMColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);

    // Then
    ASSERT_TRUE(material1 == material2);
}

TEST_F(NMMaterialTest, EqualityOperator_ColorNotEqual)
{
    // Given
    NMMaterial material1(NMColor(0.9f, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);
    NMMaterial material2(NMColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);

    // Then
    ASSERT_FALSE(material1 == material2);
}

TEST_F(NMMaterialTest, EqualityOperator_AmbientNotEqual)
{
    // Given
    NMMaterial material1(NMColor(1, 1, 1), 0.2f, 0.9f, 0.9f, 200.0f);
    NMMaterial material2(NMColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);

    // Then
    ASSERT_FALSE(material1 == material2);
}

TEST_F(NMMaterialTest, EqualityOperator_DiffuseNotEqual)
{
    // Given
    NMMaterial material1(NMColor(1, 1, 1), 0.1f, 0.8f, 0.9f, 200.0f);
    NMMaterial material2(NMColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);

    // Then
    ASSERT_FALSE(material1 == material2);
}

TEST_F(NMMaterialTest, EqualityOperator_SpecularNotEqual)
{
    // Given
    NMMaterial material1(NMColor(1, 1, 1), 0.1f, 0.9f, 0.8f, 200.0f);
    NMMaterial material2(NMColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);

    // Then
    ASSERT_FALSE(material1 == material2);
}

TEST_F(NMMaterialTest, EqualityOperator_ShininessNotEqual)
{
    // Given
    NMMaterial material1(NMColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);
    NMMaterial material2(NMColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 201.0f);

    // Then
    ASSERT_FALSE(material1 == material2);
}

TEST_F(NMMaterialTest, StreamInsertionOperator)
{
    // Given
    NMMaterial material(NMColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);
    std::stringstream stream;

    // When
    stream << material;

    // Then
    ASSERT_EQ(stream.str(), "Mtl(rgb(255, 255, 255), Ambient(0.10), Diffuse(0.90), Specular(0.90), Shininess(200), Reflective(0))");
}

TEST_F(NMMaterialTest, Assign_Color)
{
    // Given
    NMMaterial material;
    NMColor color(1, 1, 1);

    // When
    material.SetColor(color);

    // Then
    ASSERT_EQ(material.GetColor(), color);
}

TEST_F(NMMaterialTest, Assign_Ambient)
{
    // Given
    NMMaterial material;
    float ambient = 0.1f;

    // When
    material.SetAmbient(ambient);

    // Then
    ASSERT_FLOAT_EQ(material.GetAmbient(), ambient);
}

TEST_F(NMMaterialTest, Assign_Diffuse)
{
    // Given
    NMMaterial material;
    float diffuse = 0.9f;

    // When
    material.SetDiffuse(diffuse);

    // Then
    ASSERT_FLOAT_EQ(material.GetDiffuse(), diffuse);
}

TEST_F(NMMaterialTest, Assign_Specular)
{
    // Given
    NMMaterial material;
    float specular = 0.9f;

    // When
    material.SetSpecular(specular);

    // Then
    ASSERT_FLOAT_EQ(material.GetSpecular(), specular);
}

TEST_F(NMMaterialTest, Assign_Shininess)
{
    // Given
    NMMaterial material;
    float shininess = 200.0f;

    // When
    material.SetShininess(shininess);

    // Then
    ASSERT_FLOAT_EQ(material.GetShininess(), shininess);
}

// Background:
//   Given m ← material()
//   And position ← point(0, 0, 0)
//
// Scenario: Lighting with the eye between the light and the surface
//   Given eyev ← vector(0, 0, -1)
//   And normalv ← vector(0, 0, -1)
//   And light ← point_light(point(0, 0, -10), color(1, 1, 1))
//   When result ← lighting(m, light, position, eyev, normalv)
//   Then result = color(1.9, 1.9, 1.9)
TEST_F(NMMaterialTest, Lighting_EyeBetweenLightAndSurface)
{
    // Given
    NMSphere sphere;
    NMMaterial material;
    NMPoint position(0, 0, 0);
    NMVector eyev(0, 0, -1);
    NMVector normalv(0, 0, -1);
    NMPointLight light(NMPoint(0, 0, -10), NMColor(1, 1, 1));

    // When
    NMColor result = material.Lighting(sphere, light, position, eyev, normalv, false);

    // Then
    ASSERT_EQ(result, NMColor(1.9f, 1.9f, 1.9f));
}

// Background:
//   Given m ← material()
//   And position ← point(0, 0, 0)
//
// Scenario: Lighting with the eye between light and surface, eye offset 45°
//   Given eyev ← vector(0, √2/2, -√2/2)
//   And normalv ← vector(0, 0, -1)
//   And light ← point_light(point(0, 0, -10), color(1, 1, 1))
//   When result ← lighting(m, light, position, eyev, normalv)
//   Then result = color(1.0, 1.0, 1.0)
TEST_F(NMMaterialTest, Lighting_EyeBetweenLightAndSurface_EyeOffset45)
{
    // Given
    NMSphere sphere;
    NMMaterial material;
    NMPoint position(0, 0, 0);
    NMVector eyev(0, nmmath::sqrt2Over2, -nmmath::sqrt2Over2);
    NMVector normalv(0, 0, -1);
    NMPointLight light(NMPoint(0, 0, -10), NMColor(1, 1, 1));

    // When
    NMColor result = material.Lighting(sphere, light, position, eyev, normalv, false);

    // Then
    ASSERT_EQ(result, NMColor(1.0f, 1.0f, 1.0f));
}

// Background:
//   Given m ← material()
//   And position ← point(0, 0, 0)
//
// Scenario: Lighting with eye opposite surface, light offset 45°
//   Given eyev ← vector(0, 0, -1)
//   And normalv ← vector(0, 0, -1)
//   And light ← point_light(point(0, 10, -10), color(1, 1, 1))
//   When result ← lighting(m, light, position, eyev, normalv)
//   Then result = color(0.7364, 0.7364, 0.7364)
TEST_F(NMMaterialTest, Lighting_EyeOppositeSurface_LightOffset45)
{
    // Given
    NMSphere sphere;
    NMMaterial material;
    NMPoint position(0, 0, 0);
    NMVector eyev(0, 0, -1);
    NMVector normalv(0, 0, -1);
    NMPointLight light(NMPoint(0, 10, -10), NMColor(1, 1, 1));

    // When
    NMColor result = material.Lighting(sphere, light, position, eyev, normalv, false);

    // Then
    ASSERT_EQ(result, NMColor(0.736396f, 0.736396f, 0.736396f));
}

// Background:
//   Given m ← material()
//   And position ← point(0, 0, 0)
//
// Scenario: Lighting with eye in the path of the reflection vector
//   Given eyev ← vector(0, -√2/2, -√2/2)
//   And normalv ← vector(0, 0, -1)
//   And light ← point_light(point(0, 10, -10), color(1, 1, 1))
//   When result ← lighting(m, light, position, eyev, normalv)
//   Then result = color(1.6364, 1.6364, 1.6364)
TEST_F(NMMaterialTest, Lighting_EyeInPathOfReflectionVector)
{
    // Given
    NMSphere sphere;
    NMMaterial material;
    NMPoint position(0, 0, 0);
    NMVector eyev(0, -nmmath::sqrt2Over2, -nmmath::sqrt2Over2);
    NMVector normalv(0, 0, -1);
    NMPointLight light(NMPoint(0, 10, -10), NMColor(1, 1, 1));

    // When
    NMColor result = material.Lighting(sphere, light, position, eyev, normalv, false);

    // Then
    ASSERT_EQ(result, NMColor(1.636385f, 1.636385f, 1.636385f));
}

// Background:
//   Given m ← material()
//   And position ← point(0, 0, 0)
//
// Scenario: Lighting with the light behind the surface
//   Given eyev ← vector(0, 0, -1)
//   And normalv ← vector(0, 0, -1)
//   And light ← point_light(point(0, 0, 10), color(1, 1, 1))
//   When result ← lighting(m, light, position, eyev, normalv)
//   Then result = color(0.1, 0.1, 0.1)
TEST_F(NMMaterialTest, Lighting_LightBehindSurface)
{
    // Given
    NMSphere sphere;
    NMMaterial material;
    NMPoint position(0, 0, 0);
    NMVector eyev(0, 0, -1);
    NMVector normalv(0, 0, -1);
    NMPointLight light(NMPoint(0, 0, 10), NMColor(1, 1, 1));

    // When
    NMColor result = material.Lighting(sphere, light, position, eyev, normalv, false);

    // Then
    ASSERT_EQ(result, NMColor(0.1f, 0.1f, 0.1f));
}

// Scenario: Lighting with the surface in shadow
//   Given eyev ← vector(0, 0, -1)
//   And normalv ← vector(0, 0, -1)
//   And light ← point_light(point(0, 0, -10), color(1, 1, 1))
//   And in_shadow ← true
//   When result ← lighting(m, light, position, eyev, normalv, in_shadow)
//   Then result = color(0.1, 0.1, 0.1)
TEST_F(NMMaterialTest, Lighting_SurfaceInShadow)
{
    // Given
    NMSphere sphere;
    NMMaterial material;
    NMPoint position(0, 0, 0);
    NMVector eyev(0, 0, -1);
    NMVector normalv(0, 0, -1);
    NMPointLight light(NMPoint(0, 0, -10), NMColor(1, 1, 1));
    bool inShadow = true;

    // When
    NMColor result = material.Lighting(sphere, light, position, eyev, normalv, inShadow);

    // Then
    ASSERT_EQ(result, NMColor(0.1f, 0.1f, 0.1f));
}

// Scenario: Lighting with a pattern applied
//   Given m.pattern ← stripe_pattern(color(1, 1, 1), color(0, 0, 0))
//   And m.ambient ← 1
//   And m.diffuse ← 0
//   And m.specular ← 0
//   And eyev ← vector(0, 0, -1)
//   And normalv ← vector(0, 0, -1)
//   And light ← point_light(point(0, 0, -10), color(1, 1, 1))
//   When c1 ← lighting(m, light, point(0.9, 0, 0), eyev, normalv, false)
//   And c2 ← lighting(m, light, point(1.1, 0, 0), eyev, normalv, false)
//   Then c1 = color(1, 1, 1)
//   And c2 = color(0, 0, 0)
TEST_F(NMMaterialTest, Lighting_PatternApplied)
{
    // Given
    NMSphere sphere;
    NMMaterial material;
    material.SetPattern(std::make_shared<NMStripePattern>(NMColor(1, 1, 1), NMColor(0, 0, 0)));
    material.SetAmbient(1);
    material.SetDiffuse(0);
    material.SetSpecular(0);
    NMVector eyev(0, 0, -1);
    NMVector normalv(0, 0, -1);
    NMPointLight light(NMPoint(0, 0, -10), NMColor(1, 1, 1));

    // When
    NMColor c1 = material.Lighting(sphere, light, NMPoint(0.9f, 0, 0), eyev, normalv, false);
    NMColor c2 = material.Lighting(sphere, light, NMPoint(1.1f, 0, 0), eyev, normalv, false);

    // Then
    ASSERT_EQ(c1, NMColor(1, 1, 1));
    ASSERT_EQ(c2, NMColor(0, 0, 0));
}

// Scenario: Reflectivity for the default material
//   Given m ← material()
//   Then m.reflective = 0.0
TEST_F(NMMaterialTest, Reflectivity_Default)
{
    // Given
    NMMaterial material;

    // Then
    ASSERT_FLOAT_EQ(material.GetReflective(), 0.0f);
}
