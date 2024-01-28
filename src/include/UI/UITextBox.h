#pragma once

#include "UIElement.h"

#include "UILabel.h"

class UITextBox : public UIElement {
public:
    UITextBox(std::string t, std::string font, const SDL_Color& color);
    UITextBox(std::string t, std::string font, const SDL_Color& color, int mlength);
    ~UITextBox();

    void draw() override;
    void destroy() override;

    void place(int x, int y);
    void setText(std::string t, std::string font, const SDL_Color& color);
    void setText(std::string t, std::string font, const SDL_Color& color, int mlength);

private:
    UILabel* text;
};
