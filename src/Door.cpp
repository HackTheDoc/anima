#include "include/Game/Map/Structures/Door.h"

#include "include/Game/Game.h"
#include "include/Manager.h"
#include "include/Save.h"

Door::Door() {
    collider = nullptr;
    destRect = { 0,0, Tile::SIZE, Tile::SIZE };

    position.Zero();

    dest = "";
    destPos.Zero();
}

Door::~Door() {}

void Door::init(const Struct::Teleporter& door) {
    position = door.pos;

    dest = door.dest;
    destPos = door.dest_pos;
    destPos.x += (Tile::SIZE - Game::player->collider->rect.w) / 2;
    destPos.y += (Tile::SIZE - Game::player->collider->rect.h) / 2;

    collider = new Collider();
    collider->place(position);
    collider->rect.w = destRect.w;
    collider->rect.h = destRect.h;
}

void Door::update() {
    destRect.x = position.x - Game::camera.x;
    destRect.y = position.y - Game::camera.y;

    collider->update();
}

void Door::draw() {
    Manager::DrawFilledRect(&destRect, hue::door_open);

    collider->draw();
}

void Door::destroy() {
    delete collider;
    collider = nullptr;
}

void Door::use() {
    Game::LoadIsland(dest);
    Game::player->resetMovement();
    Game::player->interaction = Interaction::NONE;
    Game::player->setPosition(destPos);

    if (Save::Auto)
        Save::Update(Game::WorldID);
}

Struct::Teleporter Door::getStructure() {
    return {
         .pos = position,
         .dest = dest,
         .dest_pos = {
             destPos.x - (Tile::SIZE - Game::player->collider->rect.w) / 2,
             destPos.y - (Tile::SIZE - Game::player->collider->rect.h) / 2
            },
         .damage_level = 0
    };
}

