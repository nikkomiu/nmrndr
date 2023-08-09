#include "Canvas.hpp"

#include <cstdint>
#include <iostream>

inline std::ostream& writeColorToLine(std::ostream& os, std::streampos& lineLength, int color)
{
    auto startPos = os.tellp() - lineLength;

    // It fits if the color string length is 3 or less from the line limit of 70
    bool fits = startPos <= 67 || (color < 100 && startPos <= 68) || (color < 10 && startPos <= 69);
    if (!fits)
    {
        os.seekp(-1, std::ios_base::cur);
        os << "\n";
        lineLength = os.tellp();
    }

    os << color << " ";
    return os;
}

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

std::ostream& NMCanvas::ToPPM(std::ostream& os) const
{
    os << "P3\n";
    os << GetWidth() << " " << GetHeight() << "\n";
    os << "255\n";

    for (auto& row : pixels)
    {
        auto lineStartPos = os.tellp();

        for (auto& pixel : row)
        {
            writeColorToLine(os, lineStartPos, pixel.GetClampedRed());
            writeColorToLine(os, lineStartPos, pixel.GetClampedGreen());
            writeColorToLine(os, lineStartPos, pixel.GetClampedBlue());
        }

        // Go back one character to remove the trailing space and add a newline
        os.seekp(-1, std::ios_base::cur);
        os << "\n";
    }

    return os;
}
