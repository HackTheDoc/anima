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
    UILabel* lbl_title;

    UIButton* btn_quit;
    UIButton* btn_load;
};
