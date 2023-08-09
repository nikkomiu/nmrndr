#pragma once

#include <iomanip>
#include <iostream>

#include "Math.hpp"

class NMVector;

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

    NMPoint operator+(const NMVector &vector) const;
    NMVector operator-(const NMPoint &point) const;
    NMPoint operator-(const NMVector &point) const;
    NMPoint operator-() const;

    void operator+=(const NMVector &vector);
    void operator+=(const NMPoint &point);
    void operator-=(const NMVector &vector);

    friend std::ostream &operator<<(std::ostream &os, const NMPoint &point)
    {
        os << std::fixed << std::setprecision(2);
        os << "(" << point.x << ", " << point.y << ", " << point.z << ")";
        return os;
    }

protected:

    float x;
    float y;
    float z;
};
