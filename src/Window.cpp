#include "include/Window.h"

#include "include/Manager.h"
#include "include/Save.h"
#include "include/KeyMap.h"

#include "include/WindowState/WindowStates.h"

#include <chrono>
#include <sstream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

SDL_Window* Window::window = nullptr;

const std::string Window::title = "Anima";
bool Window::isRunning = false;

bool Window::fullscreen = false;
Text::Language Window::language = Text::Language::ENGLISH;

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
        title.c_str(),
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
    Manager::SetRenderDrawColor(hue::white);

    // load config
    std::ifstream infile("./config.json");
    json config;
    infile >> config;
    infile.close();

    Window::language = config["language"];

    Uint32 mode = config["window mode"];
    SetWindowMode(mode);

    Save::Auto = config["autosave"];

    Tutorial::activated = config["tutorial"];

    KeyMap::Load();

    // init components
    manager = new Manager();
    manager->loadFonts();

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
    manager->clear();
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

    if (!Save::Exist(wid))
        Save::Create(wid);

    Game::WorldID = wid;

    manager->removeWindowState(WindowState::Type::MAIN);
    manager->addWindowState(WindowState::Type::GAME, new Game());

    manager->addWindowState(WindowState::Type::CINEMATIC, new Cinematic("introduction"));
    manager->setCurrentWindowState(WindowState::Type::CINEMATIC);
}

void Window::quitGame() {
    if (Save::Auto && !Game::player->has_died())
        Save::Update(Game::WorldID);

    // SAVE PLAY TIME

    std::chrono::time_point<std::chrono::system_clock> endTime = std::chrono::system_clock::now();
    std::chrono::nanoseconds currentSessionTime = endTime - Game::StartTime;

    std::ifstream infile("./config.json");
    json config;
    infile >> config;
    infile.close();

    /// parse previous chrono
    std::string timeString = config["world " + std::to_string(Game::WorldID) + " time"];

    std::tm tm = {};
    std::istringstream ss(timeString);
    ss >> std::get_time(&tm, "%H:%M:%S");

    /// prepare new string
    auto playtime = std::chrono::system_clock::from_time_t(std::mktime(&tm)) + currentSessionTime;
    std::time_t playtime_t = std::chrono::system_clock::to_time_t(playtime);
    std::stringstream nss;
    nss << std::put_time(std::localtime(&playtime_t), "%H:%M:%S");

    /// saving it
    config["world " + std::to_string(Game::WorldID) + " time"] = nss.str();

    std::ofstream outfile("./config.json");
    outfile << std::setw(2) << config << std::endl;
    outfile.close();

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

void Window::execute(std::string cmd) {
    if (cmd == "next window mode") {
        WindowState* ws = manager->getCurrentState();
        OptionsMenu* om = static_cast<OptionsMenu*>(ws);

        om->next("window mode");

        return;
    }

    if (cmd == "next language") {
        WindowState* ws = manager->getCurrentState();
        OptionsMenu* om = static_cast<OptionsMenu*>(ws);

        om->next("language");

        return;
    }

    if (cmd == "open url discord") {
        WindowState* ws = manager->getCurrentState();
        Credits* cr = static_cast<Credits*>(ws);

        cr->useHyperlink("discord");

        return;
    }

    if (cmd == "open url twitter") {
        WindowState* ws = manager->getCurrentState();
        Credits* cr = static_cast<Credits*>(ws);

        cr->useHyperlink("twitter");

        return;
    }

    if (cmd == "open url github") {
        WindowState* ws = manager->getCurrentState();
        Credits* cr = static_cast<Credits*>(ws);

        cr->useHyperlink("github");

        return;
    }
}

void Window::SetWindowMode(Uint32 mode) {
    SDL_SetWindowFullscreen(window, mode);
    SDL_GetWindowSize(window, &screen.w, &screen.h);

    fullscreen = (mode == SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (!fullscreen)
        screen = { 0,0,1280,720 };

    if (!Window::isRunning)
        return;

    manager->reloadFonts();

    WindowState* ws = manager->getCurrentState();
    OptionsMenu* om = static_cast<OptionsMenu*>(ws);
    om->reload();

    SaveConfig();
}

void Window::SetLanguage(Text::Language lg) {
    Window::language = lg;

    WindowState* ws = manager->getCurrentState();
    OptionsMenu* om = static_cast<OptionsMenu*>(ws);
    om->reload();

    SaveConfig();
}

void Window::SaveConfig() {
    std::ifstream infile("./config.json");
    json config;
    infile >> config;
    infile.close();

    if (Window::fullscreen)
        config["window mode"] = SDL_WINDOW_FULLSCREEN_DESKTOP;
    else
        config["window mode"] = 0;

    config["language"] = Window::language;

    config["autosave"] = Save::Auto;

    config["tutorial"] = Tutorial::activated;

    std::ofstream outfile("./config.json");
    outfile << std::setw(2) << config << std::endl;
    outfile.close();
}
