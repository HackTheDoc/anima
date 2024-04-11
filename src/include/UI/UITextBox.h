#pragma once

#include "UIElement.h"

#include "UILabel.h"

class UITextBox : public UIElement {
public:
    UITextBox(const std::string& text, const std::string& font, const SDL_Color& color);
    UITextBox(const std::string& text, const std::string& font, const SDL_Color& color, const int mlength);
    ~UITextBox();

    void draw() override;
    void destroy() override;

    void place(const int x, const int y);
    void setText(const std::string& text, const std::string& font, const SDL_Color& color);
    void setText(const std::string& text, const std::string& font, const SDL_Color& color, const int mlength);

private:
    UILabel* lbl;
};
