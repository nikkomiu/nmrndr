#pragma once

#include "NMCore/Camera.hpp"
#include "NMCore/Canvas.hpp"
#include "NMCore/World.hpp"

struct SDL_Renderer;
struct SDL_Window;

class Application
{
public:
    Application(std::size_t width, std::size_t height);
    ~Application();

    void SetTitle(const char* title);

    int Run();

    virtual NMWorld LoadWorld() = 0;
    virtual NMCamera LoadScene() = 0;

    int WindowEventCallback(void* sdlEvent);

    void ResizeWindow(std::size_t width, std::size_t height, bool updateSDL = true);

protected:

    bool isRunning = true;

    const char* windowTitle = "NMRNDR";

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    std::size_t windowWidth = 800;
    std::size_t windowHeight = 600;

    bool Initialize();
    void ProcessInput();
    void DrawFrame(NMCanvas* canvas);
};
