#pragma once

#include "Color.hpp"
#include "Light/Point.hpp"
#include "NMM/Util.hpp"

class NMMaterial
{
public:

    NMMaterial() = default;

    NMMaterial(const NMColor &color, float ambient, float diffuse, float specular, float shininess)
        : color(color), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess)
    {
    }

    bool operator==(const NMMaterial &other) const
    {
        return color == other.color && nmmath::FloatEquals(ambient, other.ambient)
               && nmmath::FloatEquals(diffuse, other.diffuse) && nmmath::FloatEquals(specular, other.specular)
               && nmmath::FloatEquals(shininess, other.shininess);
    }

    friend std::ostream &operator<<(std::ostream &os, const NMMaterial &material)
    {
        os << "Mat(" << material.color << ", " << std::setprecision(2) << std::fixed << "Ambient(" << material.ambient
           << "), Diffuse(" << material.diffuse << "), Specular(" << material.specular << "), Shininess("
           << std::setprecision(0) << material.shininess << "))";
        return os;
    }

    inline const NMColor &GetColor() const { return color; }
    inline float GetAmbient() const { return ambient; }
    inline float GetDiffuse() const { return diffuse; }
    inline float GetSpecular() const { return specular; }
    inline float GetShininess() const { return shininess; }

    inline void SetColor(const NMColor &newColor) { color = newColor; }
    inline void SetAmbient(float newAmbient) { ambient = newAmbient; }
    inline void SetDiffuse(float newDiffuse) { diffuse = newDiffuse; }
    inline void SetSpecular(float newSpecular) { specular = newSpecular; }
    inline void SetShininess(float newShininess) { shininess = newShininess; }

    NMColor Lighting(const NMPointLight &light, const NMPoint &point, const NMVector &eyeVector,
                     const NMVector &normalVector, bool inShadow) const
    {
        // Combine the surface color with the light's color/intensity
        NMColor effectiveColor = color * light.GetColor();

        // Find the direction to the light source
        NMVector lightVector = (light.GetPosition() - point).Normalized();

        // Compute the ambient contribution
        NMColor ambientColor = effectiveColor * ambient;

        // LightDotNormal represents the cosine of the angle between the
        // light vector and the normal vector. A negative number means the
        // light is on the other side of the surface.
        float lightDotNormal = lightVector.DotProduct(normalVector);
        if (lightDotNormal < 0 || inShadow)
        {
            return ambientColor;
        }

        // Compute the diffuse contribution
        NMColor diffuseColor = effectiveColor * diffuse * lightDotNormal;

        // ReflectDotEye represents the cosine of the angle between the
        // reflection vector and the eye vector. A negative number means the
        // light reflects away from the eye.
        NMVector reflectVector = (-lightVector).Reflect(normalVector);
        float reflectDotEye = reflectVector.DotProduct(eyeVector);
        if (reflectDotEye <= 0)
        {
            return ambientColor + diffuseColor;
        }

        // Compute the specular contribution
        float factor = static_cast<float>(pow(reflectDotEye, shininess));
        NMColor specularColor = light.GetColor() * specular * factor;

        return ambientColor + diffuseColor + specularColor;
    }

protected:

    NMColor color = NMColor(1, 1, 1);
    float ambient = 0.1f;
    float diffuse = 0.9f;
    float specular = 0.9f;
    float shininess = 200.0f;
};
