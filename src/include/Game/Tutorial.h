#pragma once

#include "../UI/UILabel.h"

class Tutorial {
public:
    enum Step {
        NONE,

        OPEN_INVENTORY,
        OPEN_QUESTS,
        OPEN_BENEDICTIONS,
        USE_CONTROL_POWER,
        MOVEMENTS,

        FINISHED
    };
    static Step current;

    static bool activated;

    static void Init(const int id);

    static void Render();
    static void Destroy();

    static void Complete(const Step id);

private:
    static SDL_Rect container;
    static UILabel* content;

    static void Load(const int id);
};
