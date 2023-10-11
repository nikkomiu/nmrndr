#pragma once

#include <cstdint>
#include <iomanip>
#include <iostream>

#include "NMM/Util.hpp"

class NMColor
{
public:

    NMColor() : r(0.0f), g(0.0f), b(0.0f) {}
    NMColor(float r, float g, float b) : r(r), g(g), b(b) {}

    inline float GetRed() const { return r; }
    inline float GetGreen() const { return g; }
    inline float GetBlue() const { return b; }

    inline float operator[](std::size_t channel)
    {
        switch (channel)
        {
            case 0:
                return r;

            case 1:
                return g;

            case 2:
                return b;

            case 3:
                return 1.0f;  // alpha channel

            default:
                return 0.0f;
        }
    }

    inline int GetClampedRed() const { return static_cast<int>(nmmath::Clamp(r, 0.0f, 1.0f) * 255.0f); }
    inline int GetClampedGreen() const { return static_cast<int>(nmmath::Clamp(g, 0.0f, 1.0f) * 255.0f); }
    inline int GetClampedBlue() const { return static_cast<int>(nmmath::Clamp(b, 0.0f, 1.0f) * 255.0f); }

    bool operator==(const NMColor& other) const
    {
        return nmmath::FloatEquals(r, other.r) && nmmath::FloatEquals(g, other.g) && nmmath::FloatEquals(b, other.b);
    }

    NMColor operator+(const NMColor& color) const { return NMColor(r + color.r, g + color.g, b + color.b); }

    NMColor operator-(const NMColor& color) const { return NMColor(r - color.r, g - color.g, b - color.b); }

    NMColor operator*(float scalar) const { return NMColor(r * scalar, g * scalar, b * scalar); }

    NMColor operator*(const NMColor& color) const { return NMColor(r * color.r, g * color.g, b * color.b); }

    void operator+=(const NMColor& color)
    {
        r += color.r;
        g += color.g;
        b += color.b;
    }

    void operator-=(const NMColor& color)
    {
        r -= color.r;
        g -= color.g;
        b -= color.b;
    }

    void operator*=(float scalar)
    {
        r *= scalar;
        g *= scalar;
        b *= scalar;
    }

    void operator*=(const NMColor& color)
    {
        r *= color.r;
        g *= color.g;
        b *= color.b;
    }

    friend std::ostream& operator<<(std::ostream& os, const NMColor& vector)
    {
        os << std::fixed << std::setprecision(0);
        os << "rgb(" << vector.r * 255 << ", " << vector.g * 255 << ", " << vector.b * 255 << ")";
        return os;
    }

protected:

    float r;
    float g;
    float b;
};
