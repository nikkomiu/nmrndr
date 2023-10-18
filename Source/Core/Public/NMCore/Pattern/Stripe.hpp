#pragma once

#include "NMCore/Pattern/PatternBase.hpp"

class NMStripePattern : public NMPatternBase
{
public:

    NMStripePattern(const NMColor& colorA, const NMColor& colorB, const NMMatrix& transform = NMMatrix::Identity4x4())
        : NMPatternBase(transform), colorA(colorA), colorB(colorB)
    {
    }

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
