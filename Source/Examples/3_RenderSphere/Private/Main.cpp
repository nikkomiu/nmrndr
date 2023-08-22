#include "World.hpp"

int main(int /* argc */, char** /* argv */)
{
    NMWorld world = NMWorld(100);

    world.Setup();
    world.Run();
    world.Save("render_sphere.ppm");

    return 0;
}
