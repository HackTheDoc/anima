#pragma once

#include <map>
#include <string>

#include "UIElement.h"
#include "UILabel.h"

#include "../Event.h"

class UILanguageSelector : public UIElement {
protected:
    UILabel* lbl_title;

    SDL_Rect selectorRect;
    std::pair<Event::ID, UILabel*> choice[2];
    bool current;

public:
    UILanguageSelector();
    ~UILanguageSelector();

    void place(const int x, const int y);

    void draw() override;
    void update() override;
    void destroy() override;

    void reload();

    void next();
};
