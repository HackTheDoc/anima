#include "include/Game/Map/Structures/Portal.h"

#include "include/Window.h"
#include "include/Save.h"

#include "include/Game/Game.h"

Portal::Portal() {
    on = false;

    collider = nullptr;
    texture = nullptr;
    srcRect = destRect = {0,0,Tile::SIZE,Tile::SIZE};
    dest = "";
    destPos.Zero();
}

Portal::~Portal() {}

void Portal::init(int x, int y, std::string dest, int destX, int destY, bool opened) {
    position = Vector2D(x, y);

    this->dest = dest;
    destPos = Vector2D(destX, destY);

    texture = Window::manager->getTexture("ground");
    srcRect = {272, 32, 16, 16};

    collider = new Collider();
    collider->place(position);
    collider->rect.w = destRect.w;
    collider->rect.h = destRect.h;

    on = opened;
}

void Portal::update() {
    destRect.x = position.x - Game::camera.x;
    destRect.y = position.y - Game::camera.y;

    collider->update();
}

void Portal::draw() {
    Manager::Draw(texture, &srcRect, &destRect);
    if (!on) Manager::DrawFilledRect(&destRect, hue::portal_off);

    collider->draw();
}

void Portal::destroy() {
    texture = nullptr;
}

void Portal::activate() {
    on = true;
    Game::player->interaction = Interaction::NONE;
}

void Portal::use() {
    if (!on) return;

    Game::LoadIsland(dest);
    Game::player->resetMovement();
    Game::player->interaction = Interaction::NONE;
    Game::player->setPosition(destPos);

    if (Save::Auto)
        Save::Update(Game::WorldID);
}

bool Portal::isActivated() {
    return on;
}

PortalStructure Portal::getStructure() {
    /*
    struct PortalStructure {
        Vector2D pos;
        std::string dest;
        Vector2D dest_pos;
        bool opened;
    };
    */

   return {
        position, 
        dest, 
        {
            destPos.x - (Tile::SIZE - Game::player->collider->rect.w) / 2,
            destPos.y - (Tile::SIZE - Game::player->collider->rect.h) / 2},
        on
    };
}
