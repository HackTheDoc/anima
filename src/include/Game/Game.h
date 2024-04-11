#pragma once

#include <map>
#include <string>
#include <chrono>

#include "../WindowStates/WindowState.h"

#include "Entities/Player.h"
#include "Island.h"

#include "Tutorial.h"
#include "Statistics.h"

#include "../UI/UI.h"

namespace Struct {
    struct Island;
};

class Game : public WindowState {
public:
    static std::chrono::time_point<std::chrono::system_clock> StartTime;
    static int WorldID;

    static Statistics stats;

    static UI* ui;

    static Island* island;
    static Player* player;
    static SDL_Rect camera;

    Game();
    ~Game();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

    static void LoadIsland(const std::string& name);

    static std::map<std::string, Struct::Island> GetExploredIslandStructures();

private:
    static std::map<std::string, Island*> exploredIslands;
};
