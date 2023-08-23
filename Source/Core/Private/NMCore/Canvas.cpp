#include "NMCore/Canvas.hpp"

#include <cstdint>
#include <iostream>

inline std::ostream& writeColorToLine(std::ostream& os, std::streampos& lineLength, int color)
{
    std::streamoff curPos = os.tellp() - lineLength;

    // It fits if the color string length is 3 or less from the line limit of 70
    bool fits = curPos <= 67 || (color < 100 && curPos <= 68) || (color < 10 && curPos <= 69);
    if (!fits)
    {
        os.seekp(-1, std::ios_base::cur);
        os << "\n";
        lineLength = os.tellp();
    }

    os << color << " ";
    return os;
}

std::ostream& NMCanvas::ToPPM(std::ostream& os) const
{
    os << "P3\n";
    os << width << " " << height << "\n";
    os << "255\n";

    std::streampos lineStartPos = 0;
    for (std::size_t i = 0; i < pixels.size(); ++i)
    {
        bool isLineStart = i % width == 0;
        if (isLineStart)
        {
            lineStartPos = os.tellp();

            if (i != 0)
            {
                // Go back one character to remove the trailing space and add a newline
                os.seekp(-1, std::ios_base::cur);
                os << "\n";
            }
        }

        writeColorToLine(os, lineStartPos, pixels[i].GetClampedRed());
        writeColorToLine(os, lineStartPos, pixels[i].GetClampedGreen());
        writeColorToLine(os, lineStartPos, pixels[i].GetClampedBlue());
    }

    os.seekp(-1, std::ios_base::cur);
    os << "\n";

    return os;
}
