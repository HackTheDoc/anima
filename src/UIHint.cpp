#include "include/UI/UIHint.h"

#include "include/Game/Game.h"
#include "include/Game/Map/Structures/Structures.h"

#include "include/Manager.h"

UIHint::UIHint(const std::string& t, const std::string f) {
    text = Manager::GenerateText(t.c_str(), Window::manager->getFont(f), hue::black, 512);
    SDL_QueryTexture(text, NULL, NULL, &destRect.w, &destRect.h);
    destRect.x = destRect.y = 0;
}

UIHint::~UIHint() {}

void UIHint::place(const int x, const int y) {
    destRect.x = x - Game::camera.x;
    destRect.y = y - Game::camera.y;
}

void UIHint::place(Portal* p) {
    place(
        p->position.x + (p->collider->rect.w - destRect.w) / 2,
        p->position.y + (p->collider->rect.h - destRect.h) / 2
    );
}

void UIHint::place(Door* d) {
    place(
        d->position.x + (d->collider->rect.w - destRect.w) / 2,
        d->position.y + (d->collider->rect.h - destRect.h) / 2
    );
}

void UIHint::place(Entity* e) {
    place(
        e->position.x +(e->width / 4 - destRect.w) / 2 ,
        e->position.y - e->height / 2
    );
}

void UIHint::place(Collider* c) {
    place(
        c->position.x + (c->rect.w - destRect.w) / 2,
        c->position.y + (c->rect.h - destRect.h) / 2
    );
}

void UIHint::draw() {
    Manager::Draw(text, nullptr, &destRect);
}
 
void UIHint::destroy() {
    SDL_DestroyTexture(text);
}
