#pragma once

#include <string>
#include <SDL2/SDL.h>

class Portal;
class Entity;
class Collider;

class UIHint {
private:
    SDL_Texture* text;
    SDL_Rect destRect;

public:
    /// @brief create a new hint
    /// @param t text of the hint
    /// @param f font to use (default: default)
    UIHint(std::string t, std::string f = "default");
    ~UIHint();

    /// @brief place at a precise position
    /// @param x x pos in pixels
    /// @param y y pos in pixels
    void place(int x, int y);

    /// @brief place at a relative position to a portal
    /// @param p portal of reference
    void place(Portal* p);

    /// @brief place at a relative position to a entity
    /// @param p entity of reference
    void place(Entity* e);

    void place(Collider* c);

    void draw();
    void destroy();
};
