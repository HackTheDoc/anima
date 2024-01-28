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

    enum buttons {
        RESUME,
        SAVE,
        QUIT,
        NUMBER_OF_BUTTONS
    };
    UIDoubleCursorButton *button[NUMBER_OF_BUTTONS];

    UILabel *label;
    
};
