#pragma once

#include "Vector.hpp"

class NMEnvironment
{
public:

    NMEnvironment() : gravity(NMVector()), wind(NMVector()) {}
    NMEnvironment(const NMVector &gravity, const NMVector &wind) : gravity(gravity), wind(wind) {}

    inline const NMVector &GetGravity() const { return gravity; }
    inline const NMVector &GetWind() const { return wind; }

protected:

    NMVector gravity;
    NMVector wind;
};
