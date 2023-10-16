#pragma once

#include <cmath>
#include <limits>

namespace nmmath
{
static constexpr float pi = static_cast<float>(M_PI);
static constexpr float halfPi = static_cast<float>(M_PI / 2.0f);
static constexpr float thirdPi = static_cast<float>(M_PI / 3.0f);
static constexpr float quarterPi = static_cast<float>(M_PI / 4.0f);

static const float sqrt2Over2 = static_cast<float>(std::sqrt(2.0f) / 2.0f);

static constexpr float rayEpsilon = 0.005f;

static constexpr float floatEpsilon = std::numeric_limits<float>::epsilon() * 10.0f;

template<typename T, typename U>
inline bool FloatEquals(T a, U b, float epsilon = floatEpsilon)
{
    static_assert(std::is_floating_point<T>::value, "T must be a floating point number type.");
    static_assert(std::is_floating_point<U>::value, "U must be a floating point number type.");

    return std::abs(a - b) < epsilon;
}

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
