#pragma once

#include <map>
#include <string>
#include <array>

#include "UIElement.h"
#include "UILabel.h"
#include "UIChoice.h"

class UIWindowModeSelector : public UIElement {
protected:
    UILabel *lbl;
    SDL_Rect selectorRect;
    std::array<UIChoice, 2> choice;

public:
    UIWindowModeSelector();
    ~UIWindowModeSelector();

    /// @brief place at a precise position
    /// @param x x pos in pixels
    /// @param y y pos in pixels
    void place(int x, int y);

    void draw() override;
    void update() override;
    void destroy() override;

    /// @brief reload the textures
    void reload();

    /// @brief next choice
    void next();
};
