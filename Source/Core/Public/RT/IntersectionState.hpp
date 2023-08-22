#pragma once

#include "NMM/Point.hpp"
#include "NMM/Vector.hpp"
#include "RT/Intersection.hpp"
#include "RT/Ray.hpp"
#include "RT/IIntersectionObject.hpp"

struct SNMIntersectionState
{
public:

    SNMIntersectionState() = default;

    SNMIntersectionState(const SNMIntersection &intersection)
    {
        t = intersection.t;
        object = intersection.object;
    }

    float t;
    const INMIntersectionObject* object;
    NMPoint point;
    NMVector eyeVector;
    NMVector normalVector;
    bool isInside = false;
};
