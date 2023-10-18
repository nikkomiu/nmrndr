#pragma once

#include <NMCore/Pattern/PatternBase.hpp>

class NMCheckerPattern : public NMPatternBase
{
public:

    NMCheckerPattern(const NMColor& colorA, const NMColor& colorB, const NMMatrix& transform = NMMatrix::Identity4x4())
        : NMPatternBase(transform), colorA(colorA), colorB(colorB)
    {
    }

    inline NMColor GetColorA() const { return colorA; }
    inline NMColor GetColorB() const { return colorB; }

    virtual NMColor ColorAt(const NMPoint& point) const override
    {
        float sum = std::floor(point.GetX()) + std::floor(point.GetY()) + std::floor(point.GetZ());

        if (std::fmod(sum, 2.0f) == 0.0f)
        {
            return colorA;
        }

        return colorB;
    }

protected:

    NMColor colorA;
    NMColor colorB;
};
