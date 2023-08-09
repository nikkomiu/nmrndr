#include "Math.hpp"

#include <cmath>
#include <limits>

namespace nmmath
{
bool FloatEquals(float a, float b)
{
    float epsilon = std::numeric_limits<float>::epsilon();
    return std::abs(a - b) < epsilon;
}
}  // namespace nmmath
