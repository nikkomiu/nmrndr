#pragma once

#include <chrono>
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

    void Run();

    virtual bool ShouldEndPlay() { return false; }

    virtual void OnBeginPlay();

    virtual void Tick(float deltaTime);

    virtual void Draw() {}

    virtual void OnEndPlay();

protected:

    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point prevTickTime;

    NMEnvironment environment;
    std::vector<std::shared_ptr<NMProjectile>> projectiles;
};
