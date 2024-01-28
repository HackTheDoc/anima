#pragma once

#include <string>

#include "UIElement.h"

class UIHyperlink : public UIElement {
public:
    UIHyperlink(std::string text, std::string url, std::string font, const SDL_Color& color);
    ~UIHyperlink();

    void place(int x, int y);

    void draw() override;
    void update() override;
    void destroy() override;

    /// @brief open the url !
    void openURL();

protected:
    std::string url;
    SDL_Texture *texture;
    SDL_Texture *cursor[2];
    SDL_Rect cursorRect[2];
    bool actived;
};
