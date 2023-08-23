#pragma once

class NMPrimitiveBase;

struct SNMIntersection
{
    float t;
    NMPrimitiveBase* object;

    SNMIntersection(float initialT, NMPrimitiveBase* initialObject) : t(initialT), object(initialObject) {}

    bool operator==(const SNMIntersection& other) const { return t == other.t && object == other.object; }
};
