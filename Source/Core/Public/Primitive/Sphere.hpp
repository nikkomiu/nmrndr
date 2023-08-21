#pragma once

#include <vector>

#include "NMM/Matrix.hpp"
#include "NMM/Point.hpp"
#include "NMM/Vector.hpp"
#include "RT/Ray.hpp"

class NMSphere
{
public:

    NMSphere() = default;

    inline NMMatrix GetTransform() const { return transform; }
    inline float GetRadius() const { return radius; }
    inline const NMPoint& GetOrigin() const { return origin; }

    inline void SetTransform(const NMMatrix& newTransform) { transform = newTransform; }

    std::vector<float> Intersect(const NMRay& ray) const
    {
        NMRay transformedRay = ray.Transformed(transform.Inverse());

        NMVector sphereToRay = transformedRay.GetOrigin() - origin;
        NMVector rayDirection = transformedRay.GetDirection();
        float a = rayDirection.DotProduct(rayDirection);
        float b = 2.0f * rayDirection.DotProduct(sphereToRay);
        float c = sphereToRay.DotProduct(sphereToRay) - 1.0f;
        float discriminant = b * b - 4.0f * a * c;

        if (discriminant < 0)
        {
            return std::vector<float>();
        }

        float t1 = static_cast<float>(-b - sqrt(discriminant)) / (2.0f * a);
        float t2 = static_cast<float>(-b + sqrt(discriminant)) / (2.0f * a);

        return std::vector<float>{t1, t2};
    }

    NMVector NormalAt(const NMPoint& worldPoint) const
    {
        NMMatrix inverseTransform = transform.Inverse();
        NMPoint objectPoint = inverseTransform * worldPoint;
        NMVector objectNormal = objectPoint - origin;
        NMVector worldNormal = inverseTransform.Transposed() * objectNormal;

        return worldNormal.Normalized();
    }

protected:

    NMMatrix transform = NMMatrix::Identity4x4();

    NMPoint origin = NMPoint(0.0f, 0.0f, 0.0f);
    float radius = 1.0f;
};
