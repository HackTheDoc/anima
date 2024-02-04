#include "include/Game/Map/Structures/Portal.h"

#include "include/Window.h"
#include "include/Manager.h"
#include "include/Save.h"

#include "include/Game/Game.h"

Portal::Portal() {
    damage_level = 0;
    collider = nullptr;
    texture = nullptr;
    dest = "";
    srcRect = destRect = { 0,0,Tile::SIZE,Tile::SIZE };
    destPos.Zero();
}

Portal::~Portal() {}

void Portal::init(int x, int y, std::string dest, int destX, int destY, int dmg_lvl) {
    position = Vector2D(x, y);

    this->dest = dest;
    destPos = Vector2D(destX, destY);

    texture = Window::manager->getTexture("ground");
    srcRect = { 272, 32, 16, 16 };

    collider = new Collider();
    collider->place(position);
    collider->rect.w = destRect.w;
    collider->rect.h = destRect.h;

    damage_level = dmg_lvl;
}

void Portal::update() {
    destRect.x = position.x - Game::camera.x;
    destRect.y = position.y - Game::camera.y;

    collider->update();
}

void Portal::draw() {
    Manager::Draw(texture, &srcRect, &destRect);
    if (!isRepaired()) Manager::DrawFilledRect(&destRect, hue::portal_off);

    collider->draw();
}

void Portal::destroy() {
    texture = nullptr;
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

    Game::LoadIsland(dest);
    Game::player->resetMovement();
    Game::player->interaction = Interaction::NONE;
    Game::player->setPosition(destPos);

    if (Save::Auto)
        Save::Update(Game::WorldID);
}

PortalStructure Portal::getStructure() {
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
