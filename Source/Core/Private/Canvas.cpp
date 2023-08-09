#include "Canvas.hpp"

#include <cstdint>
#include <sstream>

void NMCanvas::Clear(const NMColor& color)
{
    for (auto& row : pixels)
    {
        for (auto& pixel : row)
        {
            pixel = color;
        }
    }
}

void NMCanvas::SetCanvas(std::size_t width, std::size_t height, const NMColor& color)
{
    pixels.resize(height);

    for (auto& row : pixels)
    {
        row.resize(width, color);
    }
}

inline void writeColorToLine(std::stringstream& ss, std::streampos& lineLength, int color)
{
    auto startPos = ss.tellp() - lineLength;

    // It fits if the color string length is 3 or less from the line limit of 70
    bool fits = startPos <= 67 || (color < 100 && startPos <= 68) || (color < 10 && startPos <= 69);
    if (!fits)
    {
        ss.seekp(-1, std::ios_base::cur);
        ss << "\n";
        lineLength = ss.tellp();
    }

    ss << color << " ";
}

std::string NMCanvas::ToPPM() const
{
    std::stringstream ss;

    ss << "P3\n";
    ss << GetWidth() << " " << GetHeight() << "\n";
    ss << "255\n";

    for (auto& row : pixels)
    {
        auto lineStartPos = ss.tellp();

        for (auto& pixel : row)
        {
            writeColorToLine(ss, lineStartPos, pixel.GetClampedRed());
            writeColorToLine(ss, lineStartPos, pixel.GetClampedGreen());
            writeColorToLine(ss, lineStartPos, pixel.GetClampedBlue());
        }

        // Go back one character to remove the trailing space and add a newline
        ss.seekp(-1, std::ios_base::cur);
        ss << "\n";
    }

    return ss.str();
}
