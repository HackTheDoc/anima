#include "include/Manager.h"

#include "include/Window.h"

#include <vector>
#include <sstream>
#include <iostream>

Manager::Manager() {
    // Tiles
    textures["ground"]      = LoadTexture("./assets/tiles/ground.png"       );
    textures["path"]        = LoadTexture("./assets/tiles/path.png"         );

    // Entities 
    textures["player"]      = LoadTexture("./assets/sprites/player.png"     );
    textures["human"]       = LoadTexture("./assets/sprites/Human.png"      );
    textures["goblin"]      = LoadTexture("./assets/sprites/Goblin.png"     );
    textures["fairy"]       = LoadTexture("./assets/sprites/Fairy.png"     );

    textures["doll"]        = LoadTexture("./assets/sprites/Doll.png"       );

    textures["dead body"]   = LoadTexture("./assets/sprites/Dead Body.png"  );

    // UI
    textures["textbox"]     = LoadTexture("./assets/UI/textbox.png"         );

    // Items
    textures["items"]       = LoadTexture("./assets/items.png"              );

    // WIndow States
    currentWindowState = WindowState::Type::UNKNOWN;
}

Manager::~Manager() {}

void Manager::clear() {
    clearFonts();
    clearTextures();
    clearWindowStates();
}

SDL_Color Manager::SetRenderDrawColor(SDL_Color c) {
    SDL_Color temp;
    SDL_GetRenderDrawColor(Window::renderer, &temp.r, &temp.g, &temp.b, &temp.a);

    SDL_SetRenderDrawColor(Window::renderer, c.r, c.g, c.b, c.a);
    
    return temp;
}

void Manager::SetViewport(const SDL_Rect* v) {
    SDL_RenderSetViewport(Window::renderer, v);
}

/* ---------- FONT MANAGER ---------- */
TTF_Font* Manager::getFont(std::string id) {
    if (fonts.count(id) == 0)
        return nullptr;
    return fonts[id];
}

void Manager::loadFonts() {
    if (Window::fullscreen) {
        float sc = (float)Window::screen.w / 1280.0;

        fonts["h1"]             = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf"      , 160*sc);
        fonts["h2"]             = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf"      , 120*sc);
        fonts["h2 bold"]        = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf"         , 120*sc);
        fonts["h3"]             = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf"      , 76 *sc);
        fonts["h3 bold"]        = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf"         , 76 *sc);
        fonts["h4"]             = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf"      , 64 *sc);
        fonts["h4 bold"]        = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf"         , 64 *sc);

        fonts["big"]            = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf"      , 48 *sc);
        fonts["big bold"]       = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf"         , 48 *sc);
        fonts["default"]        = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf"      , 32 *sc);
        fonts["default bold"]   = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf"         , 32 *sc);
        fonts["small"]          = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf"      , 16 *sc);
    }
    else {
        fonts["h1"]             = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf"      , 160   );
        fonts["h2"]             = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf"      , 120   );
        fonts["h2 bold"]        = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf"         , 120   );
        fonts["h3"]             = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf"      , 76    );
        fonts["h3 bold"]        = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf"         , 76    );
        fonts["h4"]             = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf"      , 64    );
        fonts["h4 bold"]        = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf"         , 64    );

        fonts["big"]            = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf"      , 48    );
        fonts["big bold"]       = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf"         , 48    );
        fonts["default"]        = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf"      , 32    );
        fonts["default bold"]   = TTF_OpenFont("./assets/font/Oxanium-Bold.ttf"         , 32    );
        fonts["small"]          = TTF_OpenFont("./assets/font/Oxanium-Regular.ttf"      , 16    );
    }
}

void Manager::clearFonts() {
    for (auto f : fonts)
        TTF_CloseFont(f.second);
    fonts.clear();
}

void Manager::reloadFonts() {
    clearFonts();
    loadFonts();
}

/* ---------- TEXTURE MANAGER ---------- */

SDL_Texture* Manager::getTexture(std::string id) {
    if (textures.count(id) == 0)
        return nullptr;
    return textures[id];
}

void Manager::clearTextures() {
    for (auto t : textures)
        SDL_DestroyTexture(t.second);
    textures.clear();
}

SDL_Texture* Manager::LoadTexture(const char* filepath) {
    SDL_Surface* tmpSurface = IMG_Load(filepath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    
    if (texture == nullptr) std::cout << SDL_GetError() << std::endl;

    return texture;
}

SDL_Texture* Manager::GenerateText(const char* text, TTF_Font* font, const SDL_Color& color, const int length) {
    if (font == nullptr)
        return nullptr;

    SDL_Surface* tmpSurface = TTF_RenderUTF8_Blended_Wrapped(font, text, color, length);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Window::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return texture;
}

void Manager::Draw(SDL_Texture* text, SDL_Rect* src, SDL_Rect* dest, SDL_RendererFlip flip) {
    if (text == nullptr) return;
    SDL_RenderCopyEx(Window::renderer, text, src, dest, 0, NULL, flip);
}

void Manager::DrawRect(SDL_Rect* rect, const SDL_Color& color) {
    SDL_Color temp = SetRenderDrawColor(color);

    SDL_RenderDrawRect(Window::renderer, rect);

    SetRenderDrawColor(temp);
}

void Manager::DrawFilledRect(SDL_Rect* rect, const SDL_Color& color) {
    SDL_Color temp = SetRenderDrawColor(color);

    SDL_RenderFillRect(Window::renderer, rect);

    SetRenderDrawColor(temp);
}

void Manager::DrawLine(int x1, int y1, int x2, int y2, const SDL_Color& color) {
    SDL_Color temp = SetRenderDrawColor(color);

    SDL_RenderDrawLine(Window::renderer, x1, y1, x2, y2);

    SetRenderDrawColor(temp);
}

void Manager::DrawLosange(int x, int y, int hr, int vr, const SDL_Color& color) {
    SDL_Color t = SetRenderDrawColor(color);

    SDL_RenderDrawLine(Window::renderer, x - vr, y, x, y - hr);
    SDL_RenderDrawLine(Window::renderer, x - vr, y, x, y + hr);
    SDL_RenderDrawLine(Window::renderer, x + vr, y, x, y - hr);
    SDL_RenderDrawLine(Window::renderer, x + vr, y, x, y + hr);

    SetRenderDrawColor(t);
}

/* ---------- WINDOW STATES MANAGER ---------- */
void Manager::addWindowState(WindowState::Type id, WindowState* ws) {
    windowStates.emplace(id, ws);
    windowStates[id]->init();
}

void Manager::removeWindowState(WindowState::Type id) {
    if (windowStates.count(id) == 0)
        return
    
    windowStates[id]->clean();
    windowStates.erase(id);
    currentWindowState = previousWindowState;
}

void Manager::setCurrentWindowState(WindowState::Type id) {
    previousWindowState = currentWindowState;
    currentWindowState = id;
}

void Manager::updateCurrentWindowState() {
    windowStates[currentWindowState]->update();
}

void Manager::renderCurrentWindowState() {
    if (currentWindowState == WindowState::Type::PAUSE_MENU     ||
        currentWindowState == WindowState::Type::POWER_MENU     ||
        currentWindowState == WindowState::Type::INVENTORY_MENU
    ) {
        windowStates[WindowState::Type::GAME]->render();
    }
    windowStates[currentWindowState]->render();
}

void Manager::clearWindowStates() {
    for (auto ws : windowStates) {
        ws.second->clean();
    }
    windowStates.clear();
    
    previousWindowState = WindowState::Type::UNKNOWN;
    currentWindowState = WindowState::Type::UNKNOWN;
}

WindowState* Manager::getCurrentState() {
    return windowStates[currentWindowState];     
}

WindowState::Type Manager::getCurrentStateID() {
    return currentWindowState;
}

