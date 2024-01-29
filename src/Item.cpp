#include "include/Game/Items/Items.h"

#include "include/Window.h"
#include "include/Game/Map/Tile.h"

#include <iostream>

Item::Item()
{
    id = Item::ID::UNKNOWN;
    name = description = "";
    price = 0;
    icon = {0, 0, 32, 32};
    collider = new Collider(Tile::SIZE, Tile::SIZE);
}

Item::~Item() {}

void Item::use() {}

void Item::read()
{
    std::cout << "-> " << id << " data :" << std::endl;
    std::cout << "      name : " << name << std::endl;
    std::cout << "      description : " << description << std::endl;
    std::cout << "      price : " << price << std::endl;
}

void Item::drawIconAt(SDL_Rect rect) {
    SDL_Texture* t = Window::manager->getTexture("items");

    int ratio = std::min(std::max(1, rect.w / icon.w), std::max(1, rect.h / icon.h));

    SDL_Rect r;
    r.w = icon.w * ratio;
    r.h = icon.h * ratio;
    r.x = rect.x + (rect.w - r.w) / 2;
    r.y = rect.y + (rect.h - r.h) / 2;

    Manager::Draw(t, &icon, &r);
} 

std::string Item::to_string() {
    return name+" ("+std::to_string(price)+"G)\n"+description;
}

Item *Item::Create(Item::ID it)
{
    switch (it)
    {
    case Item::ID::LAPIS_VITAE:
        return new LapisVitae();
    default:
        return new Item();
    }
}
