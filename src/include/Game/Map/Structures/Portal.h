#pragma once

#include <string>

#include "../../Components/Collider.h"
#include "../../Components/Vector2D.h"

namespace Struct {
    struct Teleporter;
};

class Portal {
public:
    Collider* collider;
    Vector2D position;

    Portal();
    ~Portal();

    void init(const Struct::Teleporter& portal);
    void update();
    void draw();
    void destroy();

    bool isRepaired();
    void repair();

    void use();

    Struct::Teleporter getStructure();

private:
    SDL_Rect destRect;

    std::string dest;
    Vector2D destPos;

    int damage_level;
};
