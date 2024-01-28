#pragma once

#include "WindowState.h"

#include "../GifTexture.h"

#include "../UI/UIElements.h"

class MainMenu : public WindowState {
private:
    GifTexture *background;

    enum buttons {
        PLAY,
        OPTIONS,
        CREDITS,
        QUIT,
        NUMBER_OF_BUTTONS
    };
    UILeftCursorButton* button[NUMBER_OF_BUTTONS];

    enum labels {
        TITLE,
        VERSION,
        NUMBER_OF_LABELS
    };
    UILabel *label[NUMBER_OF_LABELS];

public:
    MainMenu();
    ~MainMenu();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;
};
