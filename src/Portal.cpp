#include "include/Game/Map/Structures/Portal.h"

#include "include/Window.h"
#include "include/Manager.h"
#include "include/Save.h"

#include "include/Game/Game.h"

Portal::Portal() {
    damage_level = 0;
    collider = nullptr;
    dest = "";
    destRect = { 0,0,Tile::SIZE,Tile::SIZE };
    position.Zero();
    destPos.Zero();
}

Portal::~Portal() {}

void Portal::init(const Struct::Teleporter& portal) {
    position = portal.pos;

    dest = portal.dest;
    destPos = portal.dest_pos;
    destPos.x += (Tile::SIZE - Game::player->collider->rect.w) / 2;
    destPos.y += (Tile::SIZE - Game::player->collider->rect.h) / 2;

    collider = new Collider();
    collider->place(position);
    collider->rect.w = destRect.w;
    collider->rect.h = destRect.h;

    damage_level = portal.damage_level;
}

void Portal::update() {
    destRect.x = position.x - Game::camera.x;
    destRect.y = position.y - Game::camera.y;

    collider->update();
}

void Portal::draw() {
    if (!isRepaired()) Manager::DrawFilledRect(&destRect, hue::portal_off);
    else Manager::DrawFilledRect(&destRect, hue::portal_on);

    collider->draw();
}

void Portal::destroy() {
    delete collider;
    collider = nullptr;
}

bool Portal::isRepaired() {
    return damage_level <= 0;
}

void Portal::repair() {
    if (isRepaired()) return;

    Inventory* inv = Game::player->parseInventory();

    if (inv == nullptr) {
        UI::AddPopUp("ONLY LIVING ENTITIES MAY USE A PORTAL");
        return;
    }

    if (!inv->try_consume(Item::ID::LAPIS_MAGICIS)) {
        UI::AddPopUp("YOU NEED A LAPIS MAGICIS");
        return;
    }

    damage_level = std::max(0, damage_level - 1);
    Game::player->interaction = Interaction::NONE;
}

void Portal::use() {
    if (!isRepaired()) return;

    if (Game::player->parseControlledEntity() == nullptr) {
        UI::AddPopUp("ONLY LIVING ENTITIES MAY USE A PORTAL");
        return;
    }

    Game::player->resetMovement();
    Game::player->interaction = Interaction::NONE;

    Game::LoadIsland(dest);
    Game::player->setPosition(destPos);

#ifdef DEV_MOD
    std::cout << "player placed at " << destPos << std::endl;
#endif

    if (Save::Auto)
        Save::Update(Game::WorldID);
}

Struct::Teleporter Portal::getStructure() {
    return {
         .pos = position,
         .dest = dest,
         .dest_pos = {
             destPos.x - (Tile::SIZE - Game::player->collider->rect.w) / 2,
             destPos.y - (Tile::SIZE - Game::player->collider->rect.h) / 2
            },
         .damage_level = damage_level
    };
}
