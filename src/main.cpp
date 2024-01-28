#include "include/Window.h"

Window window;

int main() {
    const int FPS = 60;
    const int FRAME_DELAY = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    if (window.init() == 0) 
        return -1;
    
    while (Window::isRunning) {
        frameStart = SDL_GetTicks();

        window.handleEvents();
        window.update();
        window.render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    window.kill();

    return 0;
}
