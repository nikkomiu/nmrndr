#include <memory>

#include "Canvas.hpp"
#include "Environment.hpp"
#include "PaperWorld.hpp"
#include "Projectile.hpp"

int main(int /* argc */, char** /* argv */)
{
    NMEnvironment environment(NMVector(0.0f, -0.1f, 0.0f), NMVector(-0.01f, 0.0f, 0.0f));
    NMCanvas canvas(900, 550);

    NMPaperWorld world(environment, canvas);

    auto projPos = NMPoint(0.0f, 1.0f, 0.0f);
    auto projVel = NMVector(1.0f, 2.0f, 0.0f).Normalized() * 11.25f;
    world.AddProjectile(std::make_shared<NMProjectile>(projPos, projVel));

    auto projPos2 = NMPoint(20.0f, 1.0f, 0.0f);
    auto projVel2 = NMVector(1.0f, 1.6f, 0.0f).Normalized() * 10.0f;
    world.AddProjectile(std::make_shared<NMProjectile>(projPos2, projVel2));

    world.Run();

    return 0;
}
