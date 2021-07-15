#include "Sandbox.h"
#include "GL/Event.h"
#include <memory>
#include <iostream>

namespace
{
    constexpr int WIDTH = 1280;
    constexpr int HEIGHT = 1080;
    const char* TITLE = "Sandbox";
    bool FULLSCREEN = false;
}


int main()
{
    {
        std::unique_ptr<Sandbox> app{ new Sandbox{ WIDTH, HEIGHT, TITLE, FULLSCREEN, { 3, 3, 16, true } } };
        app->run();
    }
    std::cin.get();
}
