#include "World.hpp"

#include <thread>

#include "Projectile.hpp"

void NMWorld::AddProjectile(std::shared_ptr<NMProjectile> projectile)
{
    projectile->SetWorld(*this);
    projectiles.push_back(projectile);
}

void NMWorld::Run()
{
    OnBeginPlay();

    while (!ShouldEndPlay())
    {
        // TODO: calculate delta time
        Tick(0.1f);

        Draw();
    }

    OnEndPlay();
}

void NMWorld::OnBeginPlay()
{
    startTime = std::chrono::steady_clock::now();

    // for (auto& projectile : projectiles)
    // {
    //     projectile->OnBeginPlay();
    // }
}

void NMWorld::Tick(float deltaTime)
{
    for (auto& projectile : projectiles)
    {
        projectile->Tick(deltaTime);
    }
}

void NMWorld::OnEndPlay()
{
    // for (auto& projectile : projectiles)
    // {
    //     projectile->OnEndPlay();
    // }
}
