#include "include/Window.h"

#include "include/Save.h"
#include "include/KeyMap.h"

#include "include/WindowStates/WindowStates.h"

#include <chrono>
#include <sstream>
#include <iostream>

using json = nlohmann::json;

SDL_Window* Window::window = nullptr;

const std::string Window::TITLE = "Anima";
bool Window::isRunning = false;

bool Window::fullscreen = false;
Language Window::language = Language::ENGLISH;

SDL_Renderer* Window::renderer = nullptr;
SDL_Rect Window::screen = { 0, 0, 1280, 720 };

Manager* Window::manager = nullptr;
Event Window::event;

Window::Window() {}

Window::~Window() {}

int Window::init() {
    // init sdl
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        return -1;

    if (IMG_Init(IMG_INIT_PNG) == 0)
        return -1;

    if (TTF_Init() != 0)
        return -1;

    // init window
    window = SDL_CreateWindow(
        TITLE.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screen.w,
        screen.h,
        SDL_WINDOW_SHOWN
    );
    if (!window)
        return -2;

    // init renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
        return -3;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    Manager::SetRenderDrawColor(hue::black);

    // load config
    const Struct::Config config = Save::LoadConfig();

    Window::language = (Language)config.language;

    SetWindowMode(config.window_mode);

    Save::Auto = config.autosave;

    Tutorial::activated = config.tutorial;

    KeyMap::Key = config.controls;

    // init components
    manager = new Manager();

    openMainMenu();

    isRunning = true;

    return true;
}

void Window::update() {
    manager->updateCurrentWindowState();
}

void Window::render() {
    SDL_RenderClear(renderer);

    manager->renderCurrentWindowState();

    SDL_RenderPresent(renderer);
}

void Window::handleEvents() {
    SDL_PollEvent(&event.e);

    switch (event.e.type) {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        event.handleKeyboardInputs();
        break;
    }
}

void Window::kill() {
    delete manager;
    manager = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

/* ----- MAIN MENU ----- */

void Window::openMainMenu() {
    manager->clearWindowStates();

    manager->addWindowState(WindowState::Type::MAIN, new MainMenu());
    manager->setCurrentWindowState(WindowState::Type::MAIN);
}

/* ----- OPTIONS ----- */

void Window::openOptionsMenu() {
    manager->addWindowState(WindowState::Type::OPTIONS_MENU, new OptionsMenu());
    manager->setCurrentWindowState(WindowState::Type::OPTIONS_MENU);
}

void Window::openGeneralOptions() {
    WindowState* ws = manager->getCurrentState();
    OptionsMenu* om = static_cast<OptionsMenu*>(ws);

    om->usePage("general");
}

void Window::openControlsOptions() {
    WindowState* ws = manager->getCurrentState();
    OptionsMenu* om = static_cast<OptionsMenu*>(ws);

    om->usePage("controls");
}

/* ----- GAME ----- */

void Window::openPlayMenu() {
    manager->addWindowState(WindowState::Type::PLAY_MENU, new PlayMenu());
    manager->setCurrentWindowState(WindowState::Type::PLAY_MENU);
}

void Window::openGame(const int wid) {
    srand(time(nullptr));

    const bool wexist = Save::Exist(wid);

    if (!wexist)
        Save::Create(wid);

    Game::WorldID = wid;

    manager->removeWindowState(WindowState::Type::MAIN);
    manager->addWindowState(WindowState::Type::GAME, new Game());

    if (!wexist) {
        manager->addWindowState(WindowState::Type::CINEMATIC, new Cinematic("introduction"));
        manager->setCurrentWindowState(WindowState::Type::CINEMATIC);
    }
    else manager->setCurrentWindowState(WindowState::Type::GAME);
}

void Window::quitGame() {
    if (Save::Auto && !Game::player->has_died())
        Save::Update(Game::WorldID);

    Save::PlayTime(Game::WorldID);

    Window::manager->clearTextures();

    openMainMenu();
}

void Window::pauseGame() {
    manager->addWindowState(WindowState::Type::PAUSE_MENU, new PauseMenu());
    manager->setCurrentWindowState(WindowState::Type::PAUSE_MENU);
}

void Window::openPowerMenu() {
    manager->addWindowState(WindowState::Type::POWER_MENU, new PowerMenu());
    manager->setCurrentWindowState(WindowState::Type::POWER_MENU);
}

void Window::openInventory(Inventory* inv) {
    if (inv == nullptr) return;

    manager->addWindowState(WindowState::Type::INVENTORY_MENU, new InventoryMenu(inv));
    manager->setCurrentWindowState(WindowState::Type::INVENTORY_MENU);
}

void Window::openQuestMenu() {
    manager->addWindowState(WindowState::Type::QUEST_MENU, new QuestMenu());
    manager->setCurrentWindowState(WindowState::Type::QUEST_MENU);
}

void Window::openDeathMenu() {
    manager->addWindowState(WindowState::Type::DEATH_MENU, new DeathMenu());
    manager->setCurrentWindowState(WindowState::Type::DEATH_MENU);
}

void Window::loadLastGameSave() {
    const int wid = Game::WorldID;
    quitGame();
    openGame(wid);
}

void Window::openIdentityMenu() {
    manager->addWindowState(WindowState::Type::IDENTITY_MENU, new IdentityMenu());
    manager->setCurrentWindowState(WindowState::Type::IDENTITY_MENU);
}

void Window::resumeGame() {
    manager->removeWindowState(manager->getCurrentStateID());

    manager->setCurrentWindowState(WindowState::Type::GAME);
}

/* ----- CREDITS ----- */

void Window::openCredits() {
    manager->removeWindowState(WindowState::Type::MAIN);
    manager->addWindowState(WindowState::Type::CREDITS, new Credits());
    manager->setCurrentWindowState(WindowState::Type::CREDITS);
}

/* ----- OTHER ----- */

void Window::SetWindowMode(const Uint32 mode) {
    SDL_SetWindowFullscreen(window, mode);
    SDL_GetWindowSize(window, &screen.w, &screen.h);

    fullscreen = (mode == SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (!fullscreen)
        screen = { 0, 0, 1280, 720 };

    if (!Window::isRunning)
        return;

    manager->reloadFonts();

    WindowState* ws = manager->getCurrentState();
    OptionsMenu* om = static_cast<OptionsMenu*>(ws);
    om->reload();

    Save::SaveConfig();
}

void Window::SetLanguage(const Language lg) {
    Window::language = lg;

    WindowState* ws = manager->getCurrentState();
    OptionsMenu* om = static_cast<OptionsMenu*>(ws);
    om->reload();

    Save::SaveConfig();
}
