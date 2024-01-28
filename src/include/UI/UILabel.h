#pragma once

#include <string>
#include "UIElement.h"

/// @brief Represent a label object to display a static text on the window
class UILabel : public UIElement {
public:
    UILabel(std::string text, std::string font, const SDL_Color& color);
    UILabel(std::string text, std::string font, const SDL_Color& color, int mlength);
    
    ~UILabel();

    void draw() override;
    void destroy() override;

    void setText(std::string text, std::string font, const SDL_Color& color);
    void setText(std::string text, std::string font, const SDL_Color& color, int mlength);
    
private:
    SDL_Texture* texture;
};
