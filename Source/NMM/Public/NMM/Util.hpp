#pragma once

#include <cmath>
#include <limits>

namespace nmmath
{
static float epsilon = std::numeric_limits<float>::epsilon();

inline bool FloatEquals(float a, float b) { return std::abs(a - b) < epsilon; }

inline float Clamp(float value, float min, float max)
{
    if (value < min)
    {
        return min;
    }

    if (value > max)
    {
        return max;
    }

    return value;
}
}  // namespace nmmath