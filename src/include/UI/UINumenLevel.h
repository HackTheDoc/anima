#pragma once

#include "UIElement.h"
#include "UILabel.h"

class UINumenLevel : public UIElement {
public:
    UINumenLevel(int x, int y, int w, int h, std::string font);
    ~UINumenLevel();

    void draw() override;
    void update() override;
    void destroy() override;
private:
    UILabel* lbl;
    UILabel* doc;
    SDL_Rect docRect;
    std::string font;
};
