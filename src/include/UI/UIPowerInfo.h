#pragma once

#include "UIElement.h"
#include "UILabel.h"
#include "UITextBox.h"

#include "../Game/Entities/Player.h"

class UIPowerInfo : public UIElement {
public:
    UIPowerInfo(Power pid, int w, int h, std::string font);
    ~UIPowerInfo();

    void draw() override;
    void update() override;
    void destroy() override;

    void place(int x, int y);

private:
    std::string font;
    UILabel* title;
    UITextBox* description;
    Power pid;
};
