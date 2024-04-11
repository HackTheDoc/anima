#pragma once

#include <string>

#include "UIElement.h"

class UIHyperlink : public UIElement {
public:
    UIHyperlink(const std::string& text, const std::string& url, const std::string& font, const SDL_Color& color);
    ~UIHyperlink();

    void place(const int x, const int y);

    void draw() override;
    void update() override;
    void destroy() override;

    void openURL();

protected:
    std::string url;

    SDL_Texture *texture;

    SDL_Texture *cursor[2];
    SDL_Rect cursorRect[2];

    bool hovered;
};
