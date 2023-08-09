#include "Point.hpp"

#include "Vector.hpp"

NMPoint NMPoint::operator+(const NMVector &vector) const { return vector + *this; }

NMVector NMPoint::operator-(const NMPoint &point) const
{
    return NMVector(x - point.GetX(), y - point.GetY(), z - point.GetZ());
}

NMPoint NMPoint::operator-(const NMVector &vector) const
{
    return NMPoint(x - vector.GetX(), y - vector.GetY(), z - vector.GetZ());
}

NMPoint NMPoint::operator-() const { return NMPoint(-x, -y, -z); }

void NMPoint::operator+=(const NMVector &vector)
{
    x += vector.GetX();
    y += vector.GetY();
    z += vector.GetZ();
}

void NMPoint::operator+=(const NMPoint &point)
{
    x += point.GetX();
    y += point.GetY();
    z += point.GetZ();
}

void NMPoint::operator-=(const NMVector &vector)
{
    x -= vector.GetX();
    y -= vector.GetY();
    z -= vector.GetZ();
}
