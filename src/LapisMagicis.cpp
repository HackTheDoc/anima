#include "include/Game/Items/LapisMagicis.h"

#include "include/Game/Game.h"
#include "include/Text.h"

#include <iostream>

LapisMagicis::LapisMagicis() {
    id = Item::ID::LAPIS_MAGICIS;
    name = "Lapis Magicis";
    description = Text::Get("A cristal containing magical power.\nIt can be use to to many great things !");
    price = 20;
    
    icon.x = icon.w * 1;
    icon.y = 0;
}

LapisMagicis::~LapisMagicis() {}

void LapisMagicis::use() {
    std::cout << "using lapis magicis" << std::endl;
}
