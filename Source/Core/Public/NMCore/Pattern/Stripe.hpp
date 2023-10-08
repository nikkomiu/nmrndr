#pragma once

#include "NMCore/Color.hpp"
#include "NMM/Point.hpp"

class NMStripePattern
{
public:

    NMStripePattern(const NMColor& colorA, const NMColor& colorB)
        : colorA(colorA)
        , colorB(colorB)
    {
    }

    inline NMColor GetColorA() const
    {
        return colorA;
    }

    inline NMColor GetColorB() const
    {
        return colorB;
    }

    NMColor ColorAt(const NMPoint& point) const
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
