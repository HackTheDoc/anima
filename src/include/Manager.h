#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "WindowStates/WindowState.h"

#include "hue.h"

class Manager {
public:
    Manager();
    ~Manager();

    static SDL_Color SetRenderDrawColor(const SDL_Color& c);

    static void SetViewport(const SDL_Rect* v);

    /* ---------- FONT MANAGER ---------- */

    TTF_Font* getFont(const std::string& id);

    /// @brief to catch up with possible window resize
    void reloadFonts();

    /* ---------- TEXTURE MANAGER ----------*/

    SDL_Texture* getTexture(const std::string& id);

    /// @brief game related textures only
    void loadGameTextures();

    /// @brief game related textures only
    void clearTextures();

    static SDL_Texture* LoadTexture(const char* filepath);

    static SDL_Texture* GenerateText(const std::string& text, const std::string& font, const SDL_Color& color, const int length = INT16_MAX, const bool centered = false);

    static void Draw(SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dest, const SDL_RendererFlip flip = SDL_FLIP_NONE);

    static void DrawRect(const SDL_Rect* rect, const SDL_Color& color);

    static void DrawFilledRect(const SDL_Rect* rect, const SDL_Color& color);

    static void DrawLine(const int x1, const int y1, const int x2, const int y2, const SDL_Color& color);

    static void DrawLosange(const int x, const int y, const int hr, const int vr, const SDL_Color& color);

    /* ---------- WINDOW STATES MANAGER ---------- */

    void addWindowState(const WindowState::Type id, WindowState* ws);

    void removeWindowState(const WindowState::Type id);

    void setCurrentWindowState(const WindowState::Type id);

    void updateCurrentWindowState();

    void renderCurrentWindowState();

    void clearWindowStates();

    WindowState* getState(const WindowState::Type id);

    WindowState* getCurrentState();

    WindowState::Type getCurrentStateID();

private:
    /* ----- FONTS ----- */

    std::map<std::string, TTF_Font*> fonts;

    void loadFonts();
    void clearFonts();

    /* ----- TEXTURES ----- */

    std::map<std::string, SDL_Texture*> textures;

    static SDL_Texture* GenerateLeftAnchoredText(const std::string& text, const std::string& font, const SDL_Color& color, const int length);
    static SDL_Texture* GenerateCenterAnchoredText(const std::string& text, const std::string& font, const SDL_Color& color, const int length);

    /* ----- WINDOW STATES ----- */

    std::map<WindowState::Type, WindowState*> windowStates;
    WindowState::Type currentWindowState, previousWindowState;
};
