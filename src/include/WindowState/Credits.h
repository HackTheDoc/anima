#pragma once

#include "WindowState.h"

#include "../GifTexture.h"

#include "../UI/UIElements.h"

class Credits : public WindowState {
private:
    GifTexture *background;

    enum links {
        DISCORD,
        TWITTER,
        GITHUB,
        NUMBER_OF_LINKS
    };
    UIHyperlink* link[NUMBER_OF_LINKS];

    enum labels {
        TITLE,
        AUTHOR,
        SOCIALS,
        EMAIL,
        NUMBER_OF_LABELS
    };
    UILabel *label[NUMBER_OF_LABELS];

    UIButton* quitButton;

public:
    Credits();
    ~Credits();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

    void useHyperlink(std::string l);
};
