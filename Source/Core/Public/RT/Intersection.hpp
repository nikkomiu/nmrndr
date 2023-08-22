#pragma once

#include "RT/IIntersectionObject.hpp"

struct SNMIntersection
{
    float t;
    INMIntersectionObject* object;

    SNMIntersection(float initialT, INMIntersectionObject* initialObject) : t(initialT), object(initialObject) {}

    bool operator==(const SNMIntersection& other) const { return t == other.t && object == other.object; }
};
