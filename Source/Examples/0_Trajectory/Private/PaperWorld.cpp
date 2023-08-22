#include "PaperWorld.hpp"

#include <fstream>
#include <iostream>

#include "Projectile.hpp"

bool NMPaperWorld::ShouldEndPlay()
{
    if (NMWorld::ShouldEndPlay())
    {
        return true;
    }

    for (auto& projectile : projectiles)
    {
        if (projectile->GetPosition().GetY() >= 0.0f)
        {
            return false;
        }
    }

    return true;
}

void NMPaperWorld::OnBeginPlay()
{
    NMWorld::OnBeginPlay();

    canvas.Clear();
}

void NMPaperWorld::Draw()
{
    NMWorld::Draw();

    std::size_t canvasHeight = canvas.GetHeight();

    for (auto& projectile : projectiles)
    {
        NMPoint pos = projectile->GetPosition();

        canvas.WritePixel(static_cast<std::size_t>(pos.GetX()), canvasHeight - static_cast<std::size_t>(pos.GetY()),
                          NMColor(1.0f, 0.0f, 0.0f));
    }
}

void NMPaperWorld::OnEndPlay()
{
    NMWorld::OnEndPlay();

    std::ofstream file("output.ppm");
    if (file.is_open())
    {
        canvas.ToPPM(file);
        file.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
}
