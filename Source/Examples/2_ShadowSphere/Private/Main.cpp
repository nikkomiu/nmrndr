#include "World.hpp"

int main(int /* argc */, char** /* argv */)
{
    NMWorld world = NMWorld(100);

    world.Run();

    return 0;
}
