#include "World.hpp"

#include "Projectile.hpp"

void NMWorld::AddProjectile(std::shared_ptr<NMProjectile> projectile)
{
    projectile->SetWorld(*this);
    projectiles.push_back(projectile);
}

void NMWorld::Tick(float deltaTime)
{
    for (auto& projectile : projectiles)
    {
        projectile->Tick(deltaTime);
        std::cout << *projectile << std::endl;
    }
}
