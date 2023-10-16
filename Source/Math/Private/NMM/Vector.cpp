#include "NMM/Vector.hpp"

#include "NMM/Point.hpp"
#include "NMM/Tuple.hpp"

NMPoint NMVector::operator+(const NMPoint &point) const
{
    return NMPoint(x + point.GetX(), y + point.GetY(), z + point.GetZ());
}

float NMVector::DotProduct(const NMPoint &point) const
{
    return x * point.GetX() + y * point.GetY() + z * point.GetZ();
}
