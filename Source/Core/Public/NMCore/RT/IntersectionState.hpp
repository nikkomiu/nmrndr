#pragma once

#include "NMCore/RT/Intersection.hpp"
#include "NMCore/RT/Ray.hpp"
#include "NMM/Point.hpp"
#include "NMM/Vector.hpp"

struct SNMIntersectionState
{
public:

    SNMIntersectionState() = default;

    // TODO: move World.hpp#PrepareState() here
    SNMIntersectionState(const SNMIntersection& intersection)
    {
        t = intersection.t;
        object = intersection.object;
    }

    float t;
    const NMPrimitiveBase* object;
    NMPoint point;
    NMPoint overPoint;
    NMVector eyeVector;
    NMVector normalVector;
    bool isInside = false;
};
