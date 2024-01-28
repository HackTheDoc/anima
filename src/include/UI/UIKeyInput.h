#pragma once

#include "UIElement.h"

#include "../Event.h"

class UIKeyInput : public UIElement {
public:
    static int Height;

    /// @brief create a new key input to choose the key associated to an event
    /// @param eid id of the associated event
    UIKeyInput(Event::ID eid);

    ~UIKeyInput();

    void draw() override;
    void update() override;
    void destroy() override;

    void reload();

    /// @brief place at a precise position
    /// @param x x pos in pixels
    /// @param y y pos in pixels
    void place(int x, int y);

private:
    /// @brief am i actived ?
    bool actived;
    
    SDL_Texture* title;
    SDL_Rect titleRect;

    /// @brief set the title depending on the registered event id
    void setTitle();

    /// @brief text of with the name of the key or "..." when selecting one
    SDL_Texture* key;
    SDL_Rect keyRect;

    /// @brief associate a new key to the event id
    void setKey();

    /// @brief id of the event associated to the key input
    Event::ID eid;
};
