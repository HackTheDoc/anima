#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "../../Components/Collider.h"
#include "../../Components/Vector2D.h"

namespace Struct {
    struct Teleporter;
};

class Door {
public:
    Collider* collider;
    Vector2D position;

    Door();
    ~Door();

    void init(const Struct::Teleporter& door);
    void update();
    void draw();
    void destroy();
    
    void use();

    Struct::Teleporter getStructure();

private:
    SDL_Rect destRect;
    
    std::string dest;
    Vector2D destPos;
};
