#pragma once

#include <string>

#include "UIElement.h"

#include "../hue.h"
#include "../Event.h"

/// @brief Represent a button object to display a static text on the window associated with a specitic event
class UIButton : public UIElement {
public:
    enum Type : char {
        DEFAULT,
        LEFT_CURSOR,
        RIGHT_CURSOR,
        DOUBLE_CURSOR
    };

    UIButton();
    UIButton(const std::string& text, const Event::ID eid, const std::string& font, const SDL_Color& color, const Type type = Type::DEFAULT);
    ~UIButton();

    void draw() override;
    void update() override;
    void destroy() override;

    void setText(const std::string& text, const std::string& font, const SDL_Color& color);

    void setID(const Event::ID id);
    Event::ID getID();

    void place(const int x, const int y);

protected:
    Event::ID eid;
    Type type;

    SDL_Texture* texture;

    bool hovered;
    SDL_Texture* hoveredTexture;
    SDL_Rect hoveredTextureRect;
};

/*

    enum ID {
        UNKNOWN,

        // MAIN MENU

        QUIT,
        PLAY,
        OPTIONS,
        CREDITS,

        // PLAY MENU

        SELECT_SAVE_1,
        SELECT_SAVE_2,
        SELECT_SAVE_3,
        SELECT_SAVE_4,
        LOAD_SAVE,
        ERASE_SAVE,
        QUIT_PLAY_MENU,

        VALID_WORLD_NAME_INPUT,
        QUIT_WORLD_NAME_INPUT,

        // PAUSE MENU

        RESUME_GAME,
        SAVE_GAME,
        QUIT_GAME,

        // SETTINGS

        QUIT_SETTINGS,
        GENERAL_SETTINGS,
        CONTROLS_SETTINGS,

        // CREDITS

        QUIT_CREDITS,

        // DEATH MENU
        LOAD_LAST_SAVE
    };
*/