#pragma once

#include <map>
#include <string>
#include <array>

#include "UIElement.h"
#include "UILabel.h"
#include "UIChoice.h"

class UILanguageSelector : public UIElement {
protected:
    /// @brief title label
    UILabel *lbl;
    SDL_Rect selectorRect;
    std::array<UIChoice, 2> choice;
    /// @brief current choice
    unsigned int current;

public:
    UILanguageSelector();
    ~UILanguageSelector();

    /// @brief place at a precise position
    /// @param x x pos in pixels
    /// @param y y pos in pixels
    void place(int x, int y);

    void draw() override;
    void update() override;
    void destroy() override;

    /// @brief reload textures
    void reload();

    /// @brief next choice
    void next();
};
