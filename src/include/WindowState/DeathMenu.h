#pragma once

#include "WindowState.h"

#include "../UI/UIElements.h"

class DeathMenu : public WindowState {
public:
    DeathMenu();
    ~DeathMenu();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

private:
    UILabel* title;
    UIDoubleCursorButton* btn_quit;
    UIDoubleCursorButton* btn_load;
};
