#pragma once

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

#include "NMM/Point.hpp"
#include "NMM/Util.hpp"
#include "NMM/Vector.hpp"

class NMTuple
{
public:

    static NMTuple CreatePoint(float x, float y, float z) { return NMTuple(x, y, z, 1.0f); }

    static NMTuple CreateVector(float x, float y, float z) { return NMTuple(x, y, z, 0.0f); }

    NMTuple() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    NMTuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    NMTuple(const NMPoint &point) : x(point.GetX()), y(point.GetY()), z(point.GetZ()), w(1.0f) {}
    NMTuple(const NMVector &vector) : x(vector.GetX()), y(vector.GetY()), z(vector.GetZ()), w(0.0f) {}

    inline float GetX() const { return x; }
    inline float GetY() const { return y; }
    inline float GetZ() const { return z; }
    inline float GetW() const { return w; }

    bool operator==(const NMTuple &other) const
    {
        return nmmath::FloatEquals(x, other.x) && nmmath::FloatEquals(y, other.y) && nmmath::FloatEquals(z, other.z)
               && nmmath::FloatEquals(w, other.w);
    }

    bool operator==(const NMPoint &point) const
    {
        return nmmath::FloatEquals(x, point.GetX()) && nmmath::FloatEquals(y, point.GetY())
               && nmmath::FloatEquals(z, point.GetZ()) && nmmath::FloatEquals(w, 1.0f);
    }

    bool operator==(const NMVector &vector) const
    {
        return nmmath::FloatEquals(x, vector.GetX()) && nmmath::FloatEquals(y, vector.GetY())
               && nmmath::FloatEquals(z, vector.GetZ()) && nmmath::FloatEquals(w, 0.0f);
    }

    NMTuple operator+(const NMTuple &other) const
    {
        return NMTuple(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    NMTuple operator-(const NMTuple &other) const
    {
        return NMTuple(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    NMTuple operator-() const { return NMTuple(-x, -y, -z, -w); }

    NMTuple operator*(float scalar) const { return NMTuple(x * scalar, y * scalar, z * scalar, w * scalar); }

    NMTuple operator/(float scalar) const { return NMTuple(x / scalar, y / scalar, z / scalar, w / scalar); }

    friend std::ostream &operator<<(std::ostream &os, const NMTuple &tuple)
    {
        os << std::fixed << std::setprecision(2);
        os << "(" << tuple.x << ", " << tuple.y << ", " << tuple.z << ", " << tuple.w << ")";
        return os;
    }

    operator NMPoint() const
    {
        if (IsPoint())
        {
            return NMPoint(x, y, z);
        }
        else
        {
            return NMPoint();
        }
    }

    operator NMVector() const
    {
        if (IsVector())
        {
            return NMVector(x, y, z);
        }
        else
        {
            return NMVector();
        }
    }

    inline bool IsVector() const { return nmmath::FloatEquals(w, 0.0f); }

    inline bool IsPoint() const { return nmmath::FloatEquals(w, 1.0f); }

    inline float SquaredMagnitude() const { return x * x + y * y + z * z; }

    inline float Magnitude() const { return std::sqrt(SquaredMagnitude()); }

    inline NMTuple Normalized() const { return *this / Magnitude(); }

protected:

    float x;
    float y;
    float z;
    float w;
};
