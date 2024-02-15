#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "../../Components/Collider.h"
#include "../../Components/Vector2D.h"

namespace Struct {
    struct Portal;
};

class Portal {
public:
    Collider* collider;
    Vector2D position;

    Portal();
    ~Portal();

    void init(const Struct::Portal& portal);
    void update();
    void draw();
    void destroy();

    bool isRepaired();
    void repair();

    void use();

    Struct::Portal getStructure();

private:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    std::string dest;
    Vector2D destPos;

    int damage_level;
};
