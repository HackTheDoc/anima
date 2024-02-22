#include "include/Game/Game.h"

#include "include/Save.h"

std::chrono::time_point<std::chrono::system_clock> Game::StartTime;

int Game::WorldID = 1;
Statistics Game::stats;

UI* Game::ui = nullptr;

Island* Game::island = nullptr;
std::map<std::string, Island*> Game::exploredIslands = {};

SDL_Rect Game::camera = {0, 0, 0, 0};
Player* Game::player = nullptr;

Game::Game() {}

Game::~Game() {}

void Game::init() {
    ui = new UI();
    player = new Player();
    island = nullptr;
    exploredIslands.clear();

    camera = Window::screen;

    stats = Save::LoadStats();
    
    player->init();
    
    ui->init();

    Game::StartTime = std::chrono::system_clock::now();
}

void Game::update() {
    if (player->has_died()) {
        Window::event.raise(Event::ID::OPEN_PLAYER_DEATH_MENU);
        return;
    }

    ui->useHint("NONE");

    player->update();
    
    island->update();

    ui->update();

    // camera
    int mapWidth, mapHeight;
    island->getSize(&mapWidth, &mapHeight);

    const int maxCameraX = mapWidth - camera.w;
    const int maxCameraY = mapHeight - camera.h;

    camera.x = player->position.x - Window::screen.w*.5;
    camera.y = player->position.y - Window::screen.h*.5;

    if (camera.x < 0) camera.x = 0;
    if (camera.y < 0) camera.y = 0;
    if (camera.x > maxCameraX) camera.x = maxCameraX;
    if (camera.y > maxCameraY) camera.y = maxCameraY;

    if (mapWidth < camera.w)
        camera.x = player->position.x - (player->collider->rect.w + camera.w) / 2;
    if (mapHeight < camera.h)
        camera.y = player->position.y - (player->collider->rect.h + camera.h) / 2;

    // statistics
    stats.update();
}

void Game::render() {
    island->render();

    player->draw();

    ui->display();
}

void Game::clean() {
    player->kill();
    
    for (auto i : exploredIslands) {
        i.second->destroy();
    }
    exploredIslands.clear();
    island = nullptr;

    ui->destroy();
}

void Game::LoadIsland(const std::string& name) {
    if (island != nullptr && island->getName() == name) return;

    if (exploredIslands.count(name))
        island = exploredIslands[name];
    else {
        island = new Island(name);
        island->init();
        exploredIslands[name] = island;
    }

    UI::AddPopUp(name, false);

#ifdef DEV_MOD
    std::cout << "loaded island " << name << std::endl;
#endif
}

std::map<std::string, Struct::Island> Game::GetExploredIslandStructures() {
    std::map<std::string, Struct::Island> islands;

    for(const auto& elt : exploredIslands)
        islands[elt.first] = elt.second->getStructure();
    
    return islands;
}
