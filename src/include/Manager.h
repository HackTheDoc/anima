#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "WindowState/WindowState.h"

#include "hue.h"

#include "Window.h"

class Manager {
public:
    Manager();
    ~Manager();

    /// @brief Clear everything from the manager
    void clear();

    /// @brief set the render draw color
    /// @param c new draw color
    /// @return old draw color
    static SDL_Color SetRenderDrawColor(SDL_Color c);

    /// @brief use nullptr to reset the viewport
    /// @param v
    static void SetViewport(const SDL_Rect* v);

    /* ---------- FONT MANAGER ---------- */

    /// @brief parse a loaded font
    /// @param id id of the font
    /// @return nullptr if font not founded
    TTF_Font* getFont(std::string id);

    void loadFonts();

    void clearFonts();

    /// @brief to catch up with possible window resize
    void reloadFonts();

    /* ---------- TEXTURE MANAGER ----------*/

    /// @brief parse a loaded texture
    /// @param id id of the texture
    /// @return nullptr if texture not founded
    SDL_Texture* getTexture(std::string id);

    void clearTextures();

    /// @brief Load an existing texture
    /// @param filepath path to the texture to load
    /// @return the loaded texture or a null pointer
    static SDL_Texture* LoadTexture(const char* filepath);
    
    /// @brief Generate a text texture
    static SDL_Texture* GenerateText(const std::string& text, TTF_Font* font, const SDL_Color& color, const int length = Window::screen.w, const bool centered = false);

    /// @brief Draw a texture on the window
    /// @param texture texture to draw
    /// @param src source rectangle on the texture
    /// @param dest destination rectangle on the window
    /// @param flip flip mode (default: none)
    static void Draw(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest, SDL_RendererFlip flip = SDL_FLIP_NONE);

    /// @brief Draw a rectangle on the window
    /// @param rect rectangle to draw
    /// @param color color of the rectangle
    static void DrawRect(SDL_Rect* rect, const SDL_Color& color);

    /// @brief Draw a filled rectangle on the window
    /// @param rect rectangle to draw
    /// @param color color of the rectangle
    static void DrawFilledRect(SDL_Rect* rect, const SDL_Color& color);

    /// @brief Draw a line on the window
    /// @param x1 pos in pixel
    /// @param y1 pos in pixel
    /// @param x2 pos in pixel
    /// @param y2 pos in pixel
    /// @param color color of the rectangle
    static void DrawLine(int x1, int y1, int x2, int y2, const SDL_Color& color);

    /// @brief Draw a losange on the window
    /// @param x center x pos in pixels
    /// @param y center y pos in pixels
    /// @param hr horizontal radius in pixels
    /// @param vr vertical radius in pixels
    /// @param color color of the rectangle
    static void DrawLosange(int x, int y, int hr, int vr, const SDL_Color& color);

    /* ---------- WINDOW STATES MANAGER ---------- */

    /// @brief add a new window state to the manager (if not existing)
    /// @param id id of the state
    /// @param ws window state to add
    void addWindowState(WindowState::Type id, WindowState* ws);

    /// @brief remove a window state from the manager
    /// @param id id of the state to remove
    void removeWindowState(WindowState::Type id);
    
    /// @brief set the current state of the window to a new one (that exist)
    /// @param id new current state id
    void setCurrentWindowState(WindowState::Type id);
    
    /// @brief update the current state of the window
    void updateCurrentWindowState();
    
    /// @brief render the current state of the window
    void renderCurrentWindowState();
    
    /// @brief clear every loaded window states
    void clearWindowStates();

    /// @brief parse the current state
    /// @return a pointer to the current state
    WindowState* getCurrentState();

    /// @brief parse the id of the current state
    /// @return id of the current state
    WindowState::Type getCurrentStateID();

private:
    std::map<std::string, TTF_Font*> fonts;

    std::map<std::string, SDL_Texture*> textures;

    std::map<WindowState::Type, WindowState*> windowStates;
    WindowState::Type currentWindowState, previousWindowState;

    static SDL_Texture* GenerateLeftAnchoredText(const std::string& text, TTF_Font* font, const SDL_Color& color, const int length);
    static SDL_Texture* GenerateCenterAnchoredText(const std::string& text, TTF_Font* font, const SDL_Color& color, const int length);
};
