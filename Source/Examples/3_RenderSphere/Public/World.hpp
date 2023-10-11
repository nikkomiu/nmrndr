#pragma once

#include <fstream>

#include "NMCore/Canvas.hpp"
#include "NMCore/Primitive/Sphere.hpp"
#include "NMCore/RT/IntersectionList.hpp"
#include "NMCore/RT/Ray.hpp"

class NMWorld
{
public:

    NMWorld(std::size_t canvasSize) : canvas(NMCanvas(canvasSize, canvasSize)) {}

    void Setup()
    {
        // Set the sphere's material
        NMMaterial sphereMaterial = NMMaterial();
        sphereMaterial.SetColor(NMColor(1.0f, 0.2f, 1.0f));
        sphere.SetMaterial(sphereMaterial);
    }

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
                std::vector<SNMIntersection> intersections = sphere.Intersect(ray);
                SNMIntersectionList intersectionList = SNMIntersectionList(intersections);
                SNMIntersection* hit = intersectionList.Hit();
                if (hit != nullptr)
                {
                    NMPoint hitPoint = ray.Position(hit->t);
                    NMVector normal = sphere.NormalAt(hitPoint);
                    NMVector eye = -ray.GetDirection();
                    NMColor color = sphere.GetMaterial().Lighting(sphere, pointLight, hitPoint, eye, normal, false);
                    canvas.WritePixel(x, y, color);
                }
            }
        }
    }

    void Save(std::string filename)
    {
        std::ofstream file(filename);
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
    NMPointLight pointLight = NMPointLight(NMPoint(-10.0f, 10.0f, -10.0f), NMColor(1.0f, 1.0f, 1.0f));

    float wallZ = 10.0f;

    float wallWidth = 7.0f;
    float wallHeight = 7.0f;

    NMPoint rayOrigin = NMPoint(0.0f, 0.0f, -5.0f);
};
