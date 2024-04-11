#pragma once

#include <string>

#include "UIElement.h"
#include "UIButton.h"
#include "UILabel.h"

#include "../Event.h"

class UIInputField : public UIElement {
public:
    std::string input;

    /// @brief am i actived ?
    bool actived;

    /// @brief create a new input field popup
    /// @param title_text 
    /// @param placeholder_text 
    /// @param eid event raised when clicking the 'valid' button
    /// @param max max length of the input
    UIInputField(const std::string& title_text, const std::string& placeholder_text, const Event::ID eid, const int max);
    ~UIInputField();

    void update() override;
    void draw() override;
    void destroy() override;
    
    void place(const int x, const int y);

private:
    /// @brief max length of the input
    int inputLengthMax;
    SDL_Rect inputRect;

    UILabel *title;
    UILabel *placeholder;
    UILabel *text;

    UIButton *btn;
};
