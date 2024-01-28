#pragma once

#include <string>
#include <vector>
#include <SDL2/SDL.h>

/// TODO: optimize the gif texture by actually loading a gif image
class GifTexture {
private:
    /// @brief vectore containing every frames of the animations
    std::vector<SDL_Texture*> frames;
    
    /// @brief rect where the animation will be displayed
    SDL_Rect destRect;

    /// @brief start at 0
    int currentFrame;

    int numberOfFrames;

    /// @brief in ms
    int speed;

public:
    /// @brief load an animation from a folder containing the different frames of the gif
    /// @param path path to the gif folder
    /// @param f number of frames
    /// @param s speed (in ms)
    /// @param dest destination rectangle to display the texture
    GifTexture(std::string path, int f, int s, SDL_Rect dest);

    ~GifTexture();

    /// @brief update the current frame
    void play();
    
    /// @brief draw the current frame
    void draw();

    /// @brief destroy every frames
    void destroy();
};
