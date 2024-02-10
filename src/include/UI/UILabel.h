#pragma once

#include <string>
#include "UIElement.h"

/// @brief Represent a label object to display a static text on the window
class UILabel : public UIElement {
public:
    UILabel();
    UILabel(const std::string& text, const std::string& font, const SDL_Color& color, const int mlength = -1, const bool centered = false);
    
    ~UILabel();

    void draw() override;
    void destroy() override;

    void setText(const std::string& text, const std::string& font, const SDL_Color& color, int mlength = -1, const bool centered = false);
    
private:
    SDL_Texture* texture;
};
