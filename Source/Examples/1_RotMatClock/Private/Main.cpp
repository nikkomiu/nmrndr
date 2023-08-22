#include <cstdint>
#include <fstream>

#include "Canvas.hpp"
#include "NMM/Matrix.hpp"

int main(int /* argc */, char** /* argv */)
{
    NMCanvas canvas(100, 100);
    const NMPoint noonPoint = NMPoint(0.0f, 0.0f, 45.0f);

    float canvasHalfWidth = static_cast<float>(canvas.GetWidth()) / 2.0f;
    float canvasHalfHeight = static_cast<float>(canvas.GetHeight()) / 2.0f;
    for (int i = 0; i < 12; i++)
    {
        NMMatrix hourHand = NMMatrix::RotationY(static_cast<float>(i * (2 * M_PI / 12)));
        NMPoint hand = hourHand * noonPoint;

        std::size_t xPos = static_cast<std::size_t>(hand.GetX() + canvasHalfWidth);
        std::size_t yPos = static_cast<std::size_t>(hand.GetZ() + canvasHalfHeight);

        canvas.WritePixel(xPos, yPos, NMColor(1.0f, 1.0f, 1.0f));
    }

    std::ofstream file("clock.ppm");
    if (!file.is_open())
    {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }

    canvas.ToPPM(file);

    file.close();

    return 0;
}
