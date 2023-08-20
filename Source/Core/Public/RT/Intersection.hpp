#pragma once

struct SNMIntersection
{
    float t;
    void* object;

    SNMIntersection(float initialT, void* initialObject) : t(initialT), object(initialObject) {}

    bool operator==(const SNMIntersection& other) const { return t == other.t && object == other.object; }
};
