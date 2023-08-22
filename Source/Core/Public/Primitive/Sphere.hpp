#pragma once

#include <vector>

#include "Material.hpp"
#include "NMM/Matrix.hpp"
#include "NMM/Point.hpp"
#include "NMM/Vector.hpp"
#include "RT/IIntersectionObject.hpp"
#include "RT/Intersection.hpp"
#include "RT/Ray.hpp"

class NMSphere : public INMIntersectionObject
{
public:

    NMSphere() = default;

    virtual ~NMSphere() = default;

    virtual bool operator==(const INMIntersectionObject& other) const override
    {
        const NMSphere& otherSphere = static_cast<const NMSphere&>(other);
        return transform == otherSphere.transform && origin == otherSphere.origin && radius == otherSphere.radius;
    }

    inline virtual NMMatrix GetTransform() const override { return transform; }
    inline virtual void SetTransform(const NMMatrix& newTransform) override { transform = newTransform; }

    inline float GetRadius() const { return radius; }
    inline const NMPoint& GetOrigin() const { return origin; }

    virtual std::vector<SNMIntersection> Intersect(const NMRay& ray) override
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
            return std::vector<SNMIntersection>();
        }

        float t1 = static_cast<float>(-b - sqrt(discriminant)) / (2.0f * a);
        float t2 = static_cast<float>(-b + sqrt(discriminant)) / (2.0f * a);

        SNMIntersection int1 = SNMIntersection(t1, this);
        SNMIntersection int2 = SNMIntersection(t2, this);

        return std::vector<SNMIntersection>{int1, int2};
    }

    virtual NMVector NormalAt(const NMPoint& worldPoint) const override
    {
        NMMatrix inverseTransform = transform.Inverse();
        NMPoint objectPoint = inverseTransform * worldPoint;
        NMVector objectNormal = objectPoint - origin;
        NMVector worldNormal = inverseTransform.Transposed() * objectNormal;

        return worldNormal.Normalized();
    }

    inline virtual const NMMaterial& GetMaterial() const override { return material; }
    inline virtual void SetMaterial(const NMMaterial& newMaterial) override { material = newMaterial; }

protected:

    NMMatrix transform = NMMatrix::Identity4x4();

    NMPoint origin = NMPoint(0.0f, 0.0f, 0.0f);
    float radius = 1.0f;

    NMMaterial material;
};
