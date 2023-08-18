#pragma once

#include <iomanip>
#include <iostream>

#include "NMM/Util.hpp"
#include "NMM/Vector.hpp"

class NMPoint
{
public:

    NMPoint() : x(0.0f), y(0.0f), z(0.0f) {}
    NMPoint(float x, float y, float z) : x(x), y(y), z(z) {}

    inline float GetX() const { return x; }
    inline float GetY() const { return y; }
    inline float GetZ() const { return z; }

    bool operator==(const NMPoint &other) const
    {
        return nmmath::FloatEquals(x, other.x) && nmmath::FloatEquals(y, other.y) && nmmath::FloatEquals(z, other.z);
    }

    NMPoint operator+(const NMVector &vector) const { return vector + *this; }

    NMVector operator-(const NMPoint &point) const
    {
        return NMVector(x - point.GetX(), y - point.GetY(), z - point.GetZ());
    }

    NMPoint operator-(const NMVector &vector) const
    {
        return NMPoint(x - vector.GetX(), y - vector.GetY(), z - vector.GetZ());
    }

    NMPoint operator-() const { return NMPoint(-x, -y, -z); }

    void operator+=(const NMVector &vector)
    {
        x += vector.GetX();
        y += vector.GetY();
        z += vector.GetZ();
    }

    void operator+=(const NMPoint &point)
    {
        x += point.x;
        y += point.y;
        z += point.z;
    }

    void operator-=(const NMVector &vector)
    {
        x -= vector.GetX();
        y -= vector.GetY();
        z -= vector.GetZ();
    }

    friend std::ostream &operator<<(std::ostream &os, const NMPoint &point)
    {
        os << std::fixed << std::setprecision(2);
        os << "(" << point.x << ", " << point.y << ", " << point.z << ")";
        return os;
    }

    // TODO: Test this method
    float DotProduct(const NMPoint &other) const { return x * other.x + y * other.y + z * other.z; }

protected:

    float x;
    float y;
    float z;
};
