#include "Vector.hpp"

#include "Point.hpp"
#include "Tuple.hpp"

NMPoint NMVector::operator+(const NMPoint &point) const
{
    return NMPoint(x + point.GetX(), y + point.GetY(), z + point.GetZ());
}

NMVector NMVector::operator+(const NMVector &vector) const
{
    return NMVector(x + vector.GetX(), y + vector.GetY(), z + vector.GetZ());
}

NMVector NMVector::operator-(const NMVector &vector) const
{
    return NMVector(x - vector.GetX(), y - vector.GetY(), z - vector.GetZ());
}

NMVector NMVector::operator-() const { return NMVector(-x, -y, -z); }

NMVector NMVector::operator*(float scalar) const { return NMVector(x * scalar, y * scalar, z * scalar); }

void NMVector::operator+=(const NMVector &vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
}

void NMVector::operator-=(const NMVector &vector)
{
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
}

void NMVector::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

NMVector NMVector::operator/(float scalar) const { return NMVector(x / scalar, y / scalar, z / scalar); }

void NMVector::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
}

void NMVector::Normalize() { *this /= Magnitude(); }

float NMVector::DotProduct(const NMVector &other) const
{
    return x * other.GetX() + y * other.GetY() + z * other.GetZ();
}

NMVector NMVector::CrossProduct(const NMVector &other) const
{
    return NMVector(y * other.GetZ() - z * other.GetY(), z * other.GetX() - x * other.GetZ(),
                    x * other.GetY() - y * other.GetX());
}
