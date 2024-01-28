#pragma once

#include <string>

#include "UIElement.h"
#include "UIButtons.h"
#include "UILabel.h"

class UIInputField : public UIElement {
public:
    /// @brief contain the input lol
    std::string input;

    /// @brief am i actived ?
    bool actived;

    /// @brief create a new input field popup
    /// @param title_text title of the popup
    /// @param placeholder_text a placeholder
    /// @param id id of the valid button
    /// @param max max length of the input
    UIInputField(std::string title_text, std::string placeholder_text, UIButton::ID id, int max);
    ~UIInputField();

    void update() override;
    void draw() override;
    void destroy() override;

    /// @brief place at a precise position
    /// @param x x pos in pixels
    /// @param y y pos in pixels
    void place(int x, int y);

private:
    /// @brief max length of the input
    int inputLengthMax;
    SDL_Rect inputRect;

    UILabel *title;
    UILabel *placeholder;
    UILabel *text;

    UIButton *btn;
};
