#pragma once

#include "NMM/Point.hpp"
#include "NMM/Vector.hpp"
#include "RT/IIntersectionObject.hpp"
#include "RT/Intersection.hpp"
#include "RT/Ray.hpp"

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
    const INMIntersectionObject* object;
    NMPoint point;
    NMPoint overPoint;
    NMVector eyeVector;
    NMVector normalVector;
    bool isInside = false;
};
