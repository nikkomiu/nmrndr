#pragma once

#include "NMCore/Pattern/PatternBase.hpp"

class NMGradientPattern : public NMPatternBase
{
public:

    NMGradientPattern(const NMColor& colorA, const NMColor& colorB, const NMMatrix& transform = NMMatrix::Identity4x4())
        : NMPatternBase(transform), colorA(colorA), colorB(colorB)
    {
    }

    inline NMColor GetColorA() const { return colorA; }
    inline NMColor GetColorB() const { return colorB; }

    virtual NMColor ColorAt(const NMPoint& point) const override
    {
        NMColor distance = colorB - colorA;
        float fraction = point.GetX() - std::floor(point.GetX());

        return colorA + distance * fraction;
    }

protected:

    NMColor colorA;
    NMColor colorB;
};
