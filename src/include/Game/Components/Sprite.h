#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <stdio.h>
#include <string>

#include "Animation.h"

class Entity;

class Sprite {
public:
    int animationIndex;
    std::map<std::string, Animation> animations;
    SDL_RendererFlip spriteFlip;

    Sprite(Entity* o = nullptr);
    ~Sprite();

    /// @brief intialize the sprite
    /// @param tag name of the sprite to use
    /// @param numberOfAnimations -1 mean NO animations
    void init(const std::string& tag, const int numberOfAnimations = -1);

    /// @brief intialize the sprite
    /// @param species id of the sprite's species (for living entities only)
    /// @param numberOfAnimations -1 mean NO animations
    void init(const int species, const int numberOfAnimations = -1);

    void linkTo(Entity* entity);
    void update();
    void draw();
    void destroy();
    void setSprite(const std::string& tag);
    void play(const std::string& animationName);
    void useFrame(const int y, const int x);

private:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    bool animated;
    int frames;
    int animationSpeed; // in ms
    std::string currentAnimation;

    Entity* owner;
};
