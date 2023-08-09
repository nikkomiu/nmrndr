#include <memory>

#include "Environment.hpp"
#include "Projectile.hpp"
#include "World.hpp"

int main(int /* argc */, char** /* argv */)
{
    NMEnvironment environment(NMVector(0.0f, -0.2f, 0.0f), NMVector(-0.01f, 0.0f, 0.2f));

    auto projectile = std::make_shared<NMProjectile>(NMPoint(0.0f, 1.0f, 0.0f), NMVector(0.0f, 0.0f, 0.0f));

    NMWorld world(environment);

    world.AddProjectile(projectile);

    for (int i = 0; i < 25; ++i)
    {
        world.Tick(0.1f);
    }

    return 0;
}
