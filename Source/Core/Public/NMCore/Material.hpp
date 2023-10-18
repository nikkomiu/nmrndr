#pragma once

#include <memory>

#include "Color.hpp"
#include "Light/Point.hpp"
#include "NMM/Util.hpp"
#include "Pattern/PatternBase.hpp"

class NMMaterial
{
public:

    NMMaterial(const NMColor &color = NMColor(1, 1, 1), float ambient = 0.1f, float diffuse = 0.9f,
               float specular = 0.9f, float shininess = 200.0f, float reflective = 0.0f, float transparency = 0.0f,
               float refractiveIndex = 1.0f)
        : color(color),
          ambient(ambient),
          diffuse(diffuse),
          specular(specular),
          shininess(shininess),
          reflective(reflective),
          transparency(transparency),
          refractiveIndex(refractiveIndex)
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
        os << "Mtl(" << material.color << ", " << std::setprecision(2) << std::fixed << "Ambient(" << material.ambient;
        os << "), Diffuse(" << material.diffuse << "), Specular(" << material.specular << "), Shininess(";
        os << std::setprecision(0) << material.shininess << "), Reflective(" << material.reflective << "),";
        os << std::setprecision(2) << " Transparency(" << material.transparency << "), RefractiveIndex(";
        os << material.refractiveIndex << "))";
        return os;
    }

    inline const NMColor &GetColor() const { return color; }
    inline void SetColor(const NMColor &newColor) { color = newColor; }

    inline float GetAmbient() const { return ambient; }
    inline void SetAmbient(float newAmbient) { ambient = newAmbient; }

    inline float GetDiffuse() const { return diffuse; }
    inline void SetDiffuse(float newDiffuse) { diffuse = newDiffuse; }

    inline float GetSpecular() const { return specular; }
    inline void SetSpecular(float newSpecular) { specular = newSpecular; }

    inline float GetShininess() const { return shininess; }
    inline void SetShininess(float newShininess) { shininess = newShininess; }

    inline float GetReflective() const { return reflective; }
    inline void SetReflective(float newReflective) { reflective = newReflective; }

    inline float GetTransparency() const { return transparency; }
    inline void SetTransparency(float newTransparency) { transparency = newTransparency; }

    inline float GetRefractiveIndex() const { return refractiveIndex; }
    inline void SetRefractiveIndex(float newRefractiveIndex) { refractiveIndex = newRefractiveIndex; }

    inline std::shared_ptr<NMPatternBase> GetPattern() const { return pattern; }
    inline void SetPattern(std::shared_ptr<NMPatternBase> newPattern) { pattern = newPattern; }

    template <typename T, typename... Args> inline void SetPattern(Args &&...args)
    {
        static_assert(std::is_base_of<NMPatternBase, T>::value, "T must inherit from NMPatternBase");

        pattern = std::make_shared<T>(std::forward<Args>(args)...);
    }

    NMColor Lighting(const NMPrimitiveBase &object, const NMPointLight &light, const NMPoint &point,
                     const NMVector &eyeVector, const NMVector &normalVector, bool inShadow) const
    {
        // If the material has a pattern, use the pattern color instead of the material's color
        NMColor materialColor = pattern ? pattern->ColorAtShapePoint(object, point) : color;

        // Combine the surface color with the light's color/intensity
        NMColor effectiveColor = materialColor * light.GetColor();

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

    NMColor color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    float reflective;
    float transparency;
    float refractiveIndex;

    std::shared_ptr<NMPatternBase> pattern;
};
