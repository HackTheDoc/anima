#pragma once

#include <string>
#include <vector>

#include "UIElement.h"

/// TODO: optimize the gif texture by actually loading a gif image
class UIGifTexture : public UIElement {
public:
    /// @brief load an animation from a folder containing the different frames of the gif
    /// @param path path to the gif folder
    /// @param f number of frames
    /// @param s speed (in ms)
    /// @param dest destination rectangle to display the texture
    UIGifTexture(const std::string& path, const int f, const int s, const SDL_Rect& dest);

    ~UIGifTexture();

    void update() override;
    void draw() override;
    void destroy() override;

private:
    std::vector<SDL_Texture*> frames;

    // start at 0
    int currentFrame;

    int numberOfFrames;

    // in ms
    int speed;
};
