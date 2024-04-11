#pragma once

#include "UIButton.h"
#include "UITextBox.h"

class UIGameSaveButton : public UIButton {
public:
    UIGameSaveButton(const std::string& saveName, const int saveID, const Event::ID eid, const std::string& font, const SDL_Color& color);
    ~UIGameSaveButton();

    void draw() override;
    void update() override;
    void destroy() override;

    void place(const int x, const int y);

    bool isActive();

    /// @brief remove the informations associated with the save of the button
    void removeInfos();

private:
    bool actived;

    UITextBox* info;
};
