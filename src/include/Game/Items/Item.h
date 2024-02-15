#pragma once

#include <string>
#include <SDL2/SDL.h>

#include "../Components/Collider.h"

namespace Struct {
    struct Item;
};

class Item {
public:
    enum ID {
        UNKNOWN,
        LAPIS_VITAE,
        LAPIS_MEMORIAE,
        LAPIS_MAGICIS,
        IGNOTUM
    };
    Item::ID id;

    std::string name;
    std::string description;
    int price;

    Collider* collider;

    Item();
    ~Item();

    virtual bool use();
    virtual void read();

    void drawIconAt(SDL_Rect rect);

    std::string to_string();

    static Item *Create(Item::ID it);

    Struct::Item getStructure();

protected:
    SDL_Rect icon;
};