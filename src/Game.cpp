#include "include/Game/Game.h"

#include "include/Save.h"

std::chrono::time_point<std::chrono::system_clock> Game::StartTime;

int Game::WorldID = 1;
std::string Game::WorldName = "World 0";

UI* Game::ui = new UI();

Island* Game::island = nullptr;
std::map<std::string, Island*> Game::exploredIslands = {};

SDL_Rect Game::camera = {0, 0, 0, 0};
Player* Game::player = new Player();

Game::Game() {}

Game::~Game() {}

void Game::init() {
    camera = Window::screen;
    
    player->init();
    
    ui->init();

    PlayerStructure ps = Save::LoadPlayer(Game::WorldID);

    LoadIsland(ps.island);

    Game::StartTime = std::chrono::system_clock::now();
}

void Game::update() {
    ui->useHint("NONE");

    player->update();
    
    island->update();

    ui->update();

    // camerapp
    int mapWidth, mapHeight;
    island->getSize(&mapWidth, &mapHeight);
    int maxCameraX = mapWidth - camera.w;
    int maxCameraY = mapHeight - camera.h;

    camera.x = player->position.x - Window::screen.w*.5;
    camera.y = player->position.y - Window::screen.h*.5;

    if (camera.x < 0) camera.x = 0;
    if (camera.y < 0) camera.y = 0;
    if (camera.x > maxCameraX) camera.x = maxCameraX;
    if (camera.y > maxCameraY) camera.y = maxCameraY;
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

void Game::LoadIsland(std::string name) {
    if (island != nullptr && island->getName() == name) return;

    if (exploredIslands.count(name))
        island = exploredIslands[name];
    else {
        island = new Island(name);
        island->init();
        exploredIslands[name] = island;
    }
}

std::map<std::string, Island*> Game::GetExploredIslands() {
    return exploredIslands;
}
