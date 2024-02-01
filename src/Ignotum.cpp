#include "include/Game/Items/Ignotum.h"

#include "include/Game/Game.h"
#include "include/Text.h"

#include <iostream>

Ignotum::Ignotum() {
    id = Item::ID::IGNOTUM;
    name = "Ignotum";
    description = Text::Get("An unknown object who's usage been lost.");
    price = 20;
    
    icon.x = icon.w * 1;
    icon.y = 0;
}

Ignotum::~Ignotum() {}

void Ignotum::use() {
    std::cout << "using ignotum" << std::endl;
}
