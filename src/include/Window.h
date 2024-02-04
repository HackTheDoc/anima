#pragma once

#define DEV_MOD

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Manager;
#include "Event.h"
#include "Text.h"

class Inventory;

class Window {
public:
    /// @brief a title :)
    static const std::string title;
    /// @brief is this running ?
    static bool isRunning;

    /// @brief am i in fullscreen ?
    static bool fullscreen;
    /// @brief what language do i speak ?
    static Text::Language language;

    /// @brief let's begin with rendering !
    static SDL_Renderer *renderer;
    /// @brief so this is my workspace uh ?
    static SDL_Rect screen;

    /// @brief the manager really is handy
    static Manager *manager;
    /// @brief there is event ? so cool !
    static Event event;

    Window();
    ~Window();

    /// @brief initizalize subprocesses and load needed components
    int init();

    /// @brief update the window
    void update();

    /// @brief render components to the window
    void render();

    /// @brief handle user events
    void handleEvents();

    /// @brief destroy loaded components and kill runing subprocesses
    void kill();

    /* ----- MAIN MENU ----- */

    /// @brief open main menu
    void openMainMenu();

    /* ----- OPTIONS ----- */

    /// @brief open the option menu
    void openOptionsMenu();

    /// @brief open general section in the option menu
    void openGeneralOptions();

    /// @brief open control section in the option menu
    void openControlsOptions();

    /* ----- GAME ----- */

    /// @brief open the world selection menu
    void openPlayMenu();

    /// @brief open the game
    /// @param wid id of the world to load
    void openGame(int wid);

    /// @brief quit the world and save playtime
    void quitGame();

    /// @brief open pause menu
    void pauseGame();

    /// @brief open power menu
    void openPowerMenu();

    void openInventory(Inventory* inv);

    void openQuestMenu();

    /// @brief close pause menu
    void resumeGame();

    /* ----- CREDITS ----- */
    void openCredits();

    /* ----- OTHER ----- */

    /// @brief execute a specific command - non implemented command will be throw
    /// @param cmd 
    void execute(std::string cmd);

    /// @brief update the window mode
    /// @param mode new mode (use 0 for windowed mode)
    static void SetWindowMode(Uint32 mode);

    /// @brief update the language of the window
    /// @param lg new language id
    static void SetLanguage(Text::Language lg);

    /// @brief save the window configuration (mode)
    static void SaveConfig();

private:
    /// @brief the actual window
    static SDL_Window *window;
};
