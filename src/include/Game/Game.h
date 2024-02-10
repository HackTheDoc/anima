#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <chrono>

#include "../WindowState/WindowState.h"

#include "Entities/Player.h"
#include "Island.h"

#include "../UI/UI.h"

#include "Tutorial.h"

class Game : public WindowState {
public:
    static std::chrono::time_point<std::chrono::system_clock> StartTime;
    static int WorldID;
    static std::string WorldName;
    static UI* ui;
    static Island* island;
    static SDL_Rect camera;
    static Player* player;

    Game();
    ~Game();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

    static void LoadIsland(std::string name);

    static std::map<std::string, Island*> GetExploredIslands();

private:
    static std::map<std::string, Island*> exploredIslands;
};
