#include "include/Game/Items/LapisMemoriae.h"

#include "include/Game/Game.h"
#include "include/Text.h"

#include <iostream>

LapisMemoriae::LapisMemoriae() {
    id = Item::ID::LAPIS_MEMORIAE;
    name = "Lapis Memoriae";
    description = Text::Get("A cristal containing fragment of the world's memory.");
    price = 20;
    
    icon.x = icon.w * 1;
    icon.y = 0;
}

LapisMemoriae::~LapisMemoriae() {}

void LapisMemoriae::use() {
    std::cout << "using lapis memoriae" << std::endl;
}
