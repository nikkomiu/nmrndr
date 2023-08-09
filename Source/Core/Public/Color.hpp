#pragma once

#include <iomanip>
#include <iostream>

class NMColor
{
public:

    NMColor() : r(0.0f), g(0.0f), b(0.0f) {}
    NMColor(float r, float g, float b) : r(r), g(g), b(b) {}

    inline float GetRed() const { return r; }
    inline float GetGreen() const { return g; }
    inline float GetBlue() const { return b; }

    bool operator==(const NMColor& other) const { return r == other.r && g == other.g && b == other.b; }

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
