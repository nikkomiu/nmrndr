#pragma once

#include <vector>

struct SNMIntersection;
class NMRay;
class NMVector;
class NMPoint;
class NMMatrix;
class NMMaterial;

class INMIntersectionObject
{
public:

    virtual NMMatrix GetTransform() const = 0;
    virtual const NMMaterial &GetMaterial() const = 0;

    virtual void SetMaterial(const NMMaterial &newMaterial) = 0;

    // TODO: find a way to make const
    virtual std::vector<SNMIntersection> Intersect(const NMRay &ray) = 0;
    virtual NMVector NormalAt(const NMPoint &worldPoint) const = 0;

    virtual bool operator==(const INMIntersectionObject &other) const = 0;
};
