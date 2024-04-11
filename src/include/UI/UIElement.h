#pragma once

#include <SDL2/SDL.h>

class UIElement {
protected:
    SDL_Rect rect;

public:
    static const int MARGIN;
    
    virtual void draw();
    virtual void update();
    virtual void destroy();

    /// @brief place at a precise position
    /// @param x x pos in pixels
    /// @param y y pos in pixels
    void place(const int x, const int y);

    /// @brief place on the left side of the window
    /// @param y y pos in pixels (default: -1 => centered)
    /// @param span distance from the left border of the window
    void placeLeft(int y = -1, const int span = 8);

    /// @brief place on the bottom side of the window
    /// @param x x pos in pixels (default: -1 => centered)
    void placeBottom(int x = -1);

    /// @brief get x pos in pixels
    /// @return da x
    int x();

    /// @brief get y pos in pixels
    /// @return da y
    int y();

    /// @brief get width pos in pixels
    /// @return da width
    int width();

    /// @brief get height pos in pixels
    /// @return da height
    int height();
};
