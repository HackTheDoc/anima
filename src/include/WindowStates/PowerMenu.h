#pragma once

#include "WindowState.h"

#include "../UI/UIElements.h"

class PowerMenu : public WindowState {
public:
    PowerMenu();
    ~PowerMenu();

    void init() override;
    void render() override;
    void update() override;
    void clean() override;

private:
    SDL_Rect container;
    
    UILabel* lbl_title;

    UINumenLevel* numenCounter;

    UIPowerInfo* power[4];
};
 