#pragma once

#include <sstream>
#include <string>
#include <vector>

#include "Color.hpp"

#define DEFAULT_COLOR NMColor()

constexpr std::size_t DEFAULT_CANVAS_WIDTH = 10;
constexpr std::size_t DEFAULT_CANVAS_HEIGHT = 10;

class NMCanvas
{
public:

    NMCanvas() : NMCanvas(DEFAULT_CANVAS_WIDTH, DEFAULT_CANVAS_HEIGHT) {}
    NMCanvas(std::size_t width, std::size_t height, const NMColor& color = DEFAULT_COLOR)
        : width(width), height(height), pixels(width * height, color)
    {
    }

    inline std::size_t GetWidth() const { return width; }
    inline std::size_t GetHeight() const { return height; }

    inline const NMColor& ReadPixel(std::size_t x, std::size_t y) const
    {
        if (x < 0 || x >= width || y < 0 || y >= height)
        {
            static const NMColor color = DEFAULT_COLOR;
            return color;
        }

        return pixels[y * width + x];
    }

    inline void WritePixel(std::size_t x, std::size_t y, const NMColor& color)
    {
        if (x < 0 || x >= width || y < 0 || y >= height)
        {
            return;
        }

        pixels[y * width + x] = color;
    }

    void Clear(const NMColor& color = DEFAULT_COLOR) { std::fill(pixels.begin(), pixels.end(), color); }

    std::ostream& ToPPM(std::ostream& os) const;
    inline std::string ToPPM() const
    {
        std::stringstream ss;
        ToPPM(ss);
        return ss.str();
    }

protected:

    std::size_t width;
    std::size_t height;
    std::vector<NMColor> pixels;
};
