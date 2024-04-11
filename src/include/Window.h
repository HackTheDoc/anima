#pragma once

#define DEV_MOD

#include <string>

#include "Manager.h"
#include "Event.h"
#include "Text.h"

struct Inventory;

class Window {
public:
    static const std::string TITLE;
    static bool isRunning;

    static bool fullscreen;
    static Language language;

    static SDL_Renderer* renderer;
    static SDL_Rect screen;

    static Manager* manager;
    static Event event;

    Window();
    ~Window();

    int init();
    void update();
    void render();
    void handleEvents();
    void kill();

    /* ----- MAIN MENU ----- */

    void openMainMenu();

    /* ----- OPTIONS ----- */

    void openOptionsMenu();
    void openGeneralOptions();
    void openControlsOptions();

    /* ----- GAME ----- */

    void openPlayMenu();

    /// @brief open the game
    /// @param wid id of the world to load
    void openGame(const int wid);

    /// @brief quit the world and save playtime
    void quitGame();

    void pauseGame();
    void openPowerMenu();
    void openInventory(Inventory* inv);
    void openQuestMenu();
    void openDeathMenu();
    void loadLastGameSave();
    void openIdentityMenu();

    void resumeGame();

    /* ----- CREDITS ----- */
    void openCredits();

    /* ----- OTHER ----- */

    /// @brief update the window mode
    /// @param mode new mode (use 0 for windowed mode)
    static void SetWindowMode(const Uint32 mode);

    /// @brief update the language of the window
    /// @param lg new language id
    static void SetLanguage(const Language lg);

private:
    /// @brief the actual window
    static SDL_Window *window;
};
