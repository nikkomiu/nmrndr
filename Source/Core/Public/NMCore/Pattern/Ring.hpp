#pragma once

#include <NMCore/Pattern/PatternBase.hpp>

class NMRingPattern : public NMPatternBase
{
public:

    NMRingPattern(const NMColor& colorA, const NMColor& colorB, const NMMatrix& transform = NMMatrix::Identity4x4())
        : NMPatternBase(transform), colorA(colorA), colorB(colorB) {}

    inline NMColor GetColorA() const { return colorA; }
    inline NMColor GetColorB() const { return colorB; }

    virtual NMColor ColorAt(const NMPoint& point) const override
    {
        float x = point.GetX();
        float z = point.GetZ();

        float distance = std::floor(std::sqrt(x * x + z * z));

        if (std::fmod(distance, 2.0f) == 0.0f)
        {
            return colorA;
        }

        return colorB;
    }

protected:

    NMColor colorA;
    NMColor colorB;
};
