#pragma once

class WindowState {
public:
    enum Type {
        UNKNOWN,
        MAIN,
        PLAY_MENU,
        OPTIONS_MENU,
        CREDITS,
        GAME,
        PAUSE_MENU,
        POWER_MENU,
        INVENTORY_MENU,
        QUEST_MENU
    };

    WindowState() {}
    ~WindowState() {}

    virtual void init() {}
    virtual void update() {}
    virtual void render() {}
    virtual void clean() {}

    virtual void reload() {}

};
