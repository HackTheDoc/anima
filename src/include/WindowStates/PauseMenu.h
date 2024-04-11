#pragma once

#include "WindowState.h"

#include "../UI/UIElements.h"

class PauseMenu : public WindowState {
public:
    PauseMenu();
    ~PauseMenu();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

private:
    SDL_Rect container;

    UILabel* lbl_title;
    
    UIButton* btn_resume;
    UIButton* btn_save;
    UIButton* btn_quit;
};
