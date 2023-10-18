#pragma once

#include <vector>

#include "NMCore/Primitive/PrimitiveBase.hpp"

class NMSphere : public NMPrimitiveBase
{
public:

    NMSphere() = default;

    virtual ~NMSphere() = default;

    virtual bool operator==(const NMPrimitiveBase& other) const override
    {
        if (!NMPrimitiveBase::operator==(other))
        {
            return false;
        }

        const NMSphere& otherSphere = static_cast<const NMSphere&>(other);
        return radius == otherSphere.radius;
    }

    inline float GetRadius() const { return radius; }
    inline void SetRadius(float newRadius) { radius = newRadius; }

    virtual std::vector<SNMIntersection> LocalIntersect(const NMRay& localRay) const override
    {
        NMVector sphereToRay = localRay.GetOrigin() - origin;
        NMVector rayDirection = localRay.GetDirection();
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

    static NMSphere GlassSphere()
    {
        NMSphere sphere;
        NMMaterial material;
        material.SetTransparency(1.0f);
        material.SetRefractiveIndex(1.5f);
        sphere.SetMaterial(material);
        return sphere;
    }

protected:

    float radius = 1.0f;
};
