#pragma once

#include <vector>

#include "NMM/Point.hpp"
#include "NMM/Vector.hpp"
#include "RT/Ray.hpp"

class NMSphere
{
public:

    NMSphere() = default;

    inline float GetRadius() const { return radius; }
    inline const NMPoint& GetOrigin() const { return origin; }

    std::vector<float> Intersect(const NMRay& ray) const
    {
        NMVector sphereToRay = ray.GetOrigin() - origin;
        NMVector rayDirection = ray.GetDirection();
        float a = rayDirection.DotProduct(rayDirection);
        float b = 2.0f * rayDirection.DotProduct(sphereToRay);
        float c = sphereToRay.DotProduct(sphereToRay) - 1.0f;
        float discriminant = b * b - 4.0f * a * c;

        if (discriminant < 0)
        {
            return std::vector<float>();
        }

        float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b + sqrt(discriminant)) / (2.0f * a);

        return std::vector<float>{t1, t2};
    }

protected:

    NMPoint origin = NMPoint(0.0f, 0.0f, 0.0f);
    float radius = 1.0f;
};
