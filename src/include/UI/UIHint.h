#pragma once

#include <SDL2/SDL.h>

class Portal;
class Door;
class Entity;
class Collider;

#include "UILabel.h"

class UIHint {
private:
    UILabel* lbl;

public:
    UIHint(const std::string& text, const std::string& font);
    ~UIHint();

    void place(const int x, const int y);

    /// @brief place at a relative position to a portal
    /// @param p portal of reference
    void place(Portal* p);

    /// @brief place at a relative position to a door
    /// @param d door of reference
    void place(Door* d);

    /// @brief place at a relative position to a entity
    /// @param p entity of reference
    void place(Entity* e);

    void place(Collider* c);

    void draw();
    void destroy();
};
