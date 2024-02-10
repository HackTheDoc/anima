#pragma once

class WindowState {
public:
    enum Type {
        UNKNOWN,
        MAIN,
        PLAY_MENU,
        OPTIONS_MENU,
        CREDITS,
        CINEMATIC,
        GAME,
        PAUSE_MENU,
        POWER_MENU,
        INVENTORY_MENU,
        QUEST_MENU,
        DEATH_MENU
    };

    WindowState() {}
    ~WindowState() {}

    virtual void init() {}
    virtual void update() {}
    virtual void render() {}
    virtual void clean() {}

    virtual void reload() {}

};
