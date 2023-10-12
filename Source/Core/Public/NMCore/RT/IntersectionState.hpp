#pragma once

#include "NMCore/Primitive/PrimitiveBase.hpp"
#include "NMCore/RT/Intersection.hpp"
#include "NMCore/RT/Ray.hpp"
#include "NMM/Point.hpp"
#include "NMM/Vector.hpp"

struct SNMIntersectionState
{
public:

    SNMIntersectionState() = default;

    SNMIntersectionState(const SNMIntersection& intersection, const NMRay& ray)
        : t(intersection.t), object(intersection.object), point(ray.Position(t)),
          eyeVector(-ray.GetDirection()), normalVector(object->NormalAt(point))
    {
        overPoint = point + (normalVector * nmmath::rayEpsilon);
        reflectVector = ray.GetDirection().Reflect(normalVector);

        if (normalVector.DotProduct(eyeVector) < 0.0f)
        {
            isInside = true;
            normalVector = -normalVector;
        }
    }

    float t = 0.0f;
    const NMPrimitiveBase* object = nullptr;
    NMPoint point = NMPoint();
    NMPoint overPoint = NMPoint();
    NMVector eyeVector = NMVector();
    NMVector normalVector = NMVector();
    NMVector reflectVector = NMVector();
    bool isInside = false;
};
