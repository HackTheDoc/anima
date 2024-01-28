#pragma once

#include <string>

#include "UIElement.h"

#include "../hue.h"

/// @brief what a nice button object
class UIButton : public UIElement {
public:
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
    };

    /// @brief create a useless button
    UIButton();

    /// @brief create a new button
    /// @param text text
    /// @param w width of the button
    /// @param h height of the button
    /// @param id id of the button
    /// @param font font to use
    /// @param color color to use (default: white)
    UIButton(std::string text, UIButton::ID id, std::string font, const SDL_Color& color = hue::white);

    /// @brief create a new button
    /// @param text text
    /// @param w width of the button
    /// @param h height of the button
    /// @param id id of the button
    /// @param font font to use
    /// @param color color to use (default: white)
    UIButton(std::string text, int w, int h, UIButton::ID id, std::string font, const SDL_Color& color = hue::white);

    ~UIButton();

    void draw() override;
    void update() override;
    void destroy() override;


    /// @brief set the text of the button
    /// @param text text
    /// @param font font to use
    /// @param color color to use
    void setText(std::string text, std::string font, const SDL_Color& color);

    /// @brief set the button id
    /// @param id new button id
    void setID(UIButton::ID id);

    /// @brief parse the button id
    /// @return actual id
    UIButton::ID getID();

    /// @brief place at a precise position
    /// @param x x pos in pixels
    /// @param y y pos in pixels
    void place(int x, int y);

protected:
    UIButton::ID id;

    SDL_Texture* texture;

    bool hovered;
    SDL_Texture* hoveredTexture;
    SDL_Rect hoveredTextureRect;
};

/// @brief classical button but with a cursor on the left side
class UILeftCursorButton : public UIButton {
public:
    /// @brief create a new button
    /// @param text text
    /// @param id id of the button
    /// @param font font to use
    /// @param color color to use
    UILeftCursorButton(std::string text, UIButton::ID id, std::string font, const SDL_Color& color);

    /// @brief create a new button
    /// @param text text
    /// @param w width of the button
    /// @param h height of the button
    /// @param id id of the button
    /// @param font font to use
    /// @param color color to use
    UILeftCursorButton(std::string text, int w, int h, UIButton::ID id, std::string font, const SDL_Color& color);
    ~UILeftCursorButton();

    /// @brief place at a precise position
    /// @param x x pos in pixels
    /// @param y y pos in pixels
    void place(int x, int y);
};

/// @brief classical button but with cursor on both left and right sides
class UIDoubleCursorButton : public UIButton {
public:
    /// @brief create a new button
    /// @param text text
    /// @param id id of the button
    /// @param font font to use
    /// @param color color to use
    UIDoubleCursorButton(std::string text, UIButton::ID id, std::string font, const SDL_Color& color);

    /// @brief create a new button
    /// @param text text
    /// @param w width of the button
    /// @param h height of the button
    /// @param id id of the button
    /// @param font font to use
    /// @param color color to use
    UIDoubleCursorButton(std::string text, int w, int h, UIButton::ID id, std::string font, const SDL_Color& color);
    ~UIDoubleCursorButton();
};
