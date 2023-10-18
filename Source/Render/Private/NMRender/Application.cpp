#include "NMRender/Application.hpp"

#include <SDL2/SDL.h>

#define DEBUG_DRAW_TIME 0

NMColor bilinearInterp(NMCanvas* canvas, float x, float y)
{
    std::size_t x0 = static_cast<std::size_t>(x);
    std::size_t y0 = static_cast<std::size_t>(y);
    std::size_t x1 = x0 + 1;
    std::size_t y1 = y0 + 1;

    auto alpha = x - static_cast<float>(x0);
    double beta = y - static_cast<float>(y0);

    auto px100 = canvas->ReadPixel(x0, y0);
    auto px101 = canvas->ReadPixel(x1, y0);
    auto px110 = canvas->ReadPixel(x0, y1);
    auto px111 = canvas->ReadPixel(x1, y1);

    float colChan[3] = {};
    for (std::size_t i = 0; i < 3; i++)
    {
        colChan[i] = static_cast<float>((1 - alpha) * (1 - beta) * px100[i] + alpha * (1 - beta) * px101[i]
                                        + (1 - alpha) * beta * px110[i] + alpha * beta * px111[i]);
    }
    return NMColor(colChan[0], colChan[1], colChan[2]);
}

Application::Application(std::size_t width, std::size_t height) : windowWidth(width), windowHeight(height) {}

Application::~Application()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Application::SetTitle(const char* title)
{
    windowTitle = title;
    if (!window)
    {
        return;
    }

    SDL_SetWindowTitle(window, title);
}

int Application::Run()
{
    if (!Initialize())
    {
        return 10;
    }

    NMCanvas* canvas = new NMCanvas(windowWidth, windowHeight);
    NMWorld world = LoadWorld();
    NMCamera camera = LoadScene();

    // async render
    std::thread renderThread([&world, &camera, &canvas]() { camera.Render(world, canvas); });

#if DEBUG_DRAW_TIME
    auto startDraw = std::chrono::high_resolution_clock::now();
    auto endDraw = std::chrono::high_resolution_clock::now();
#endif
    while (isRunning)
    {
        ProcessInput();

#if DEBUG_DRAW_TIME
        startDraw = std::chrono::high_resolution_clock::now();
#endif

        DrawFrame(canvas);

#if DEBUG_DRAW_TIME
        endDraw = std::chrono::high_resolution_clock::now();

        auto drawDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endDraw - startDraw);
        printf("Draw time: %4ldms\n", drawDuration.count());
#endif
    }

    camera.StopRender();
    renderThread.join();

    return 0;
}

int Application::WindowEventCallback(void* sdlEvent)
{
    SDL_Event* event = static_cast<SDL_Event*>(sdlEvent);

    if (event->type == SDL_WINDOWEVENT)
    {
        switch (event->window.event)
        {
            case SDL_WINDOWEVENT_RESIZED:
                ResizeWindow(static_cast<std::size_t>(event->window.data1),
                             static_cast<std::size_t>(event->window.data2), false);
                break;
        }
    }

    return 1;
}

void Application::ResizeWindow(std::size_t width, std::size_t height, bool updateSDL)
{
    windowWidth = width;
    windowHeight = height;

    if (updateSDL)
    {
        SDL_SetWindowSize(window, static_cast<int>(windowWidth), static_cast<int>(windowHeight));
    }
}

bool Application::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    uint32_t flags = SDL_WINDOW_SHOWN;

    window = SDL_CreateWindow("NM RNDR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              static_cast<int>(windowWidth), static_cast<int>(windowHeight), flags);
    if (!window)
    {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return false;
    }

    // Allow resizing of the window
    SDL_SetWindowResizable(window, SDL_TRUE);

    // Register callback for this->ResizeWindow()
    SDL_AddEventWatch(
        [](void* data, SDL_Event* event) -> int
        {
            Application* app = static_cast<Application*>(data);

            if (!app)
            {
                return 1;
            }

            app->WindowEventCallback(event);

            return 1;
        },
        this);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Application::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
        }
    }

    const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
    if (keyboardState[SDL_SCANCODE_ESCAPE])
    {
        isRunning = false;
    }
}

void Application::DrawFrame(NMCanvas* canvas)
{
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    SDL_RenderClear(renderer);

    float scaleX = static_cast<float>(windowWidth) / static_cast<float>(canvas->GetWidth());
    float scaleY = static_cast<float>(windowHeight) / static_cast<float>(canvas->GetHeight());
    float scale = std::min(scaleX, scaleY);

    // Draw each pixel of the canvas to the screen
    NMColor pixelColor;
    for (std::size_t y = 0; y < windowHeight; ++y)
    {
        for (std::size_t x = 0; x < windowWidth; ++x)
        {
            auto origX = static_cast<float>(x) / scale;
            auto origY = static_cast<float>(y) / scale;

            pixelColor = bilinearInterp(canvas, origX, origY);
            SDL_SetRenderDrawColor(renderer, static_cast<uint8_t>(pixelColor.GetClampedRed()),
                                   static_cast<uint8_t>(pixelColor.GetClampedGreen()),
                                   static_cast<uint8_t>(pixelColor.GetClampedBlue()), 1.0f);
            SDL_RenderDrawPoint(renderer, static_cast<int>(x), static_cast<int>(y));
        }
    }

    SDL_RenderPresent(renderer);
}
