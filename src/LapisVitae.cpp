#include "include/Game/Items/LapisVitae.h"

#include "include/Game/Game.h"
#include "include/Text.h"

LapisVitae::LapisVitae() {
    id = Item::ID::LAPIS_VITAE;
    name = "Lapis Vitae";
    description = Text::Get("A cristal made out of the life force of a god.");
    price = 10;
    
    icon.x = icon.w * 1;
    icon.y = 0;
}

LapisVitae::~LapisVitae() {}

void LapisVitae::use() {
    Game::player->modifyNumenLevelBy(+1);
}
