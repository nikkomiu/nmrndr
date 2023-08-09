#pragma once

#include <sstream>
#include <string>
#include <vector>

#include "Color.hpp"

constexpr std::size_t DEFAULT_CANVAS_WIDTH = 10;
constexpr std::size_t DEFAULT_CANVAS_HEIGHT = 10;
constexpr float DEFAULT_CANVAS_COLOR_R = 0.0f;
constexpr float DEFAULT_CANVAS_COLOR_G = 0.0f;
constexpr float DEFAULT_CANVAS_COLOR_B = 0.0f;

class NMCanvas
{
public:

    NMCanvas() : NMCanvas(DEFAULT_CANVAS_WIDTH, DEFAULT_CANVAS_HEIGHT) {}
    NMCanvas(std::size_t width, std::size_t height) { SetCanvas(width, height); }
    NMCanvas(std::size_t width, std::size_t height, const NMColor& color) { SetCanvas(width, height, color); }

    inline std::size_t GetWidth() const { return pixels[0].size(); }
    inline std::size_t GetHeight() const { return pixels.size(); }

    inline const std::vector<std::vector<NMColor>>& GetPixelData() const { return pixels; }

    inline void WritePixel(std::size_t x, std::size_t y, const NMColor& color)
    {
        if (x < 0 || x >= GetWidth() || y < 0 || y >= GetHeight())
        {
            return;
        }

        pixels[y][x] = color;
    }

    void Clear(const NMColor& color = NMColor(DEFAULT_CANVAS_COLOR_R, DEFAULT_CANVAS_COLOR_G, DEFAULT_CANVAS_COLOR_B));

    std::ostream& ToPPM(std::ostream& os) const;
    inline std::string ToPPM() const
    {
        std::stringstream ss;
        ToPPM(ss);
        return ss.str();
    }

protected:

    std::vector<std::vector<NMColor>> pixels;

    void SetCanvas(std::size_t width, std::size_t height,
                   const NMColor& color
                   = NMColor(DEFAULT_CANVAS_COLOR_R, DEFAULT_CANVAS_COLOR_G, DEFAULT_CANVAS_COLOR_B));
};
