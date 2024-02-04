#pragma once

#include "WindowState.h"
#include "../UI/UIElements.h"

class QuestMenu : public WindowState {
public:
    QuestMenu();
    ~QuestMenu();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

private:
    SDL_Rect container;

    UILabel* title;

    UILabel* mainqt;
    UILabel* mainqc;
};
