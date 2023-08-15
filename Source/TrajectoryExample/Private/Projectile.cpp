#include "Projectile.hpp"

#include "World.hpp"

void NMProjectile::Tick(float deltaTime)
{
    position += velocity * deltaTime;
    velocity += world->GetEnvironment().GetGravity() * deltaTime;
    velocity += world->GetEnvironment().GetWind() * deltaTime;
}
