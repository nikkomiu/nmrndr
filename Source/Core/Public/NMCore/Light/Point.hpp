#pragma once

#include "NMCore/Color.hpp"
#include "NMM/Point.hpp"

class NMPointLight
{
public:

    NMPointLight() = default;

    NMPointLight(const NMPoint &position, const NMColor &color) : color(color), position(position) {}

    inline const NMColor &GetColor() const { return color; }
    inline const NMPoint &GetPosition() const { return position; }

protected:

    NMColor color;
    NMPoint position;
};
