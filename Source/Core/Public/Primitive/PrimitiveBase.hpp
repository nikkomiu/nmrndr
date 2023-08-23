#pragma once

#include "Material.hpp"
#include "NMM/Matrix.hpp"
#include "NMM/Point.hpp"
#include "NMM/Vector.hpp"
#include "RT/Intersection.hpp"
#include "RT/Ray.hpp"

class NMPrimitiveBase
{
public:

    NMPrimitiveBase() = default;
    virtual ~NMPrimitiveBase() = default;

    virtual bool operator==(const NMPrimitiveBase& other) const
    {
        return transform == other.transform &&
            material == other.material;
    }

    inline virtual NMMatrix GetTransform() const { return transform; }
    inline virtual void SetTransform(const NMMatrix& newTransform) { transform = newTransform; }

    inline virtual const NMMaterial& GetMaterial() const { return material; }
    inline virtual void SetMaterial(const NMMaterial& newMaterial) { material = newMaterial; }

    inline const NMPoint& GetOrigin() const { return origin; }

    // TODO: mark const
    inline std::vector<SNMIntersection> Intersect(const NMRay& ray)
    {
        NMRay localRay = ray.Transformed(transform.Inverse());
        return LocalIntersect(localRay);
    }

    virtual NMVector NormalAt(const NMPoint& worldPoint) const
    {
        NMMatrix inverseTransform = transform.Inverse();

        NMPoint localPoint = inverseTransform * worldPoint;
        NMVector localNormal = LocalNormalAt(localPoint);
        NMVector worldNormal = inverseTransform.Transposed() * localNormal;

        return worldNormal.Normalized();
    }

    virtual std::vector<SNMIntersection> LocalIntersect(const NMRay& localRay) = 0;
    inline virtual NMVector LocalNormalAt(const NMPoint& localPoint) const { return localPoint - origin; }

protected:

    NMMatrix transform = NMMatrix::Identity4x4();
    NMMaterial material = NMMaterial();

    NMPoint origin = NMPoint(0.0f, 0.0f, 0.0f);
};