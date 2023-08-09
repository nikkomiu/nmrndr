#pragma once

#include <memory>
#include <vector>

#include "Environment.hpp"

class NMProjectile;

class NMWorld
{
public:

    NMWorld() = default;
    NMWorld(const NMEnvironment &environment) : environment(environment) {}

    inline const NMEnvironment &GetEnvironment() const { return environment; }
    inline void SetEnvironment(const NMEnvironment &environment) { this->environment = environment; }

    void AddProjectile(std::shared_ptr<NMProjectile> projectile);
    inline void ClearProjectiles() { projectiles.clear(); }

    void Tick(float deltaTime);

protected:

    NMEnvironment environment;
    std::vector<std::shared_ptr<NMProjectile>> projectiles;
};
