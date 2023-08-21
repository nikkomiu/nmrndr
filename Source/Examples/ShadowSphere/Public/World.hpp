#pragma once

#include <fstream>

#include "Canvas.hpp"
#include "Primitive/Sphere.hpp"
#include "RT/Ray.hpp"
#include "RT/IntersectionList.hpp"

class NMWorld
{
public:

    NMWorld(std::size_t canvasSize) : canvas(NMCanvas(canvasSize, canvasSize)) {}

    void Run()
    {
        float pixelSizeHeight = wallHeight / static_cast<float>(canvas.GetHeight());
        float pixelSizeWidth = wallWidth / static_cast<float>(canvas.GetWidth());
        float halfHeight = wallHeight / 2.0f;
        float halfWidth = wallWidth / 2.0f;

        for (std::size_t y = 0; y < canvas.GetHeight(); ++y)
        {
            auto worldY = static_cast<float>(halfHeight - pixelSizeHeight * static_cast<float>(y));
            for (std::size_t x = 0; x < canvas.GetWidth(); ++x)
            {
                auto worldX = static_cast<float>(-halfWidth + pixelSizeWidth * static_cast<float>(x));
                NMPoint position = NMPoint(worldX, worldY, wallZ);

                NMRay ray = NMRay(rayOrigin, (position - rayOrigin).Normalized());
                std::vector<float> intersections = sphere.Intersect(ray);
                if (intersections.size() > 0)
                {
                    canvas.WritePixel(x, y, hitColor);
                }
            }
        }

        std::ofstream file("shadow_sphere.ppm");
        if (!file.is_open())
        {
            std::cerr << "Failed to open file" << std::endl;
            return;
        }

        canvas.ToPPM(file);

        file.close();
    }

protected:

    NMCanvas canvas;
    NMSphere sphere = NMSphere();

    float wallZ = 10.0f;

    float wallWidth = 7.0f;
    float wallHeight = 7.0f;

    NMPoint rayOrigin = NMPoint(0.0f, 0.0f, -5.0f);

    NMColor hitColor = NMColor(1.0f, 0.0f, 0.0f);
};
