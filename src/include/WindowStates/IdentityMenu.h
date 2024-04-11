#pragma once

#include "WindowState.h"

#include "../UI/UIElements.h"

class IdentityMenu : public WindowState {
public:
    IdentityMenu();
    ~IdentityMenu();

    void init() override;
    void render() override;
    void clean() override;

private:
    SDL_Rect container;

    UILabel* lbl_title;
    UILabel* lbl_name;
    UILabel* lbl_powerLevel;
    UILabel* lbl_attribut;
};
