#pragma once

#include "NMM/Point.hpp"
#include "NMM/Vector.hpp"

class NMRay
{
public:

    NMRay() = default;
    NMRay(const NMPoint& initialOrigin, const NMVector& initalDirection)
        : origin(initialOrigin), direction(initalDirection)
    {
    }

    const NMPoint& GetOrigin() const { return origin; }
    const NMVector& GetDirection() const { return direction; }

    NMPoint Position(float t) const { return origin + direction * t; }

protected:

    NMPoint origin;
    NMVector direction;
};
