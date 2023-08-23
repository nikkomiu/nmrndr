#pragma once

#include "Primitive/PrimitiveBase.hpp"

class NMPlane : public NMPrimitiveBase
{
public:

    NMPlane() = default;

    inline virtual bool operator==(const NMPrimitiveBase& other) const override
    {
        if (!NMPrimitiveBase::operator==(other))
        {
            return false;
        }

        const NMPlane& otherPlane = static_cast<const NMPlane&>(other);
        return origin == otherPlane.origin;
    }

    inline virtual std::vector<SNMIntersection> LocalIntersect(const NMRay& localRay) override
    {
        if (std::abs(localRay.GetDirection().GetY()) < nmmath::floatEpsilon)
        {
            return std::vector<SNMIntersection>();
        }

        float t = -localRay.GetOrigin().GetY() / localRay.GetDirection().GetY();
        return std::vector<SNMIntersection>({ SNMIntersection(t, this) });
    }

    inline virtual NMVector LocalNormalAt(const NMPoint& /* localPoint */) const override
    {
        return NMVector(0.0f, 1.0f, 0.0f);
    }
};
