#pragma once

#include <string>
#include <SDL2/SDL.h>

#include "../Components/Collider.h"

class Item
{
public:
    enum ID
    {
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
    virtual void use();
    virtual void read();

    void drawIconAt(SDL_Rect rect);

    std::string to_string();

    static Item *Create(Item::ID it);

protected:
    SDL_Rect icon;
};