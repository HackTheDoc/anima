#pragma once

#include "UITextBox.h"
#include "UIButtons.h"

class UIGameSaveButton : public UIButton {
public:
    UIGameSaveButton(std::string sname, int sid, UIButton::ID id, std::string font, const SDL_Color& color);
    ~UIGameSaveButton();

    void draw() override;
    void update() override;
    void destroy() override;

    /// @brief place at a precise position
    /// @param x x pos in pixels
    /// @param y y pos in pixels
    void place(int x, int y);

    /// @brief am i active ?
    /// @return true if actived else false
    bool isActive();

    /// @brief remove the informations associated with the save of the button
    void removeInfos();

private:
    bool actived;

    UITextBox* info;
};
