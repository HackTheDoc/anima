#include <windows.h>
#include <iostream>

#include "include/Window.h"

Window window;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const int FPS = 60;
    const int FRAME_DELAY = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    if (window.init() < 0)
        exit(EXIT_FAILURE);

#ifdef DEV_MOD
    std::cout << "GAME IN DEBUG MOD" << std::endl;
#endif

    while (Window::isRunning) {
        frameStart = SDL_GetTicks();

        window.handleEvents();
        window.update();
        window.render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY)
            SDL_Delay(FRAME_DELAY - frameTime);
    }

    window.kill();

    exit(EXIT_SUCCESS);
}
