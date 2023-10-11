#pragma once

#include "NMCore/Pattern/Pattern.hpp"

class NMStripePattern : NMPattern
{
public:

    NMStripePattern(const NMColor& colorA, const NMColor& colorB) : colorA(colorA), colorB(colorB) {}

    inline NMColor GetColorA() const { return colorA; }
    inline NMColor GetColorB() const { return colorB; }

    virtual NMColor ColorAt(const NMPoint& point) const override
    {
        if (static_cast<int>(floor(point.GetX())) % 2 == 0)
        {
            return colorA;
        }

        return colorB;
    }

protected:

    NMColor colorA;
    NMColor colorB;
};
