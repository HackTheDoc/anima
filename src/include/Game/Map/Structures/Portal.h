#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "../../Components/Collider.h"
#include "../../Components/Vector2D.h"

struct PortalStructure {
    Vector2D pos;
    std::string dest;
    Vector2D dest_pos;
    bool opened;
};

class Portal {
public:
    Collider* collider;
    Vector2D position;

    Portal();
    ~Portal();

    void init(int x, int y, std::string dest, int destX, int destY, bool opened);
    void update();
    void draw();
    void destroy();

    void activate();
    void use();

    bool isActivated();

    PortalStructure getStructure();

private:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    std::string dest;
    Vector2D destPos;

    bool on;
};
