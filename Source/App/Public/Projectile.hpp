#pragma once

#include "Point.hpp"
#include "Vector.hpp"
#include "World.hpp"

class NMProjectile
{
public:

    NMProjectile() : position(NMPoint()), velocity(NMVector()) {}
    NMProjectile(const NMPoint& position, const NMVector& velocity) : position(position), velocity(velocity) {}

    void SetWorld(NMWorld& world) { this->world = &world; }
    inline NMWorld& GetWorld() const { return *world; }

    void Tick(float deltaTime);

    friend std::ostream& operator<<(std::ostream& os, const NMProjectile& projectile)
    {
        os << "Projectile<Loc" << projectile.position << ", Vel" << projectile.velocity << ">";
        return os;
    }

    inline const NMPoint& GetPosition() const { return position; }
    inline const NMVector& GetVelocity() const { return velocity; }

protected:

    NMWorld* world;

    NMPoint position;
    NMVector velocity;
};
