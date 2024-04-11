#pragma once

#include "UIElement.h"
#include "UILabel.h"
#include "UITextBox.h"

#include "../Game/Entities/Player.h"

class UIPowerInfo : public UIElement {
public:
    UIPowerInfo(const Power pid, const int w, const int h, const std::string& font);
    ~UIPowerInfo();

    void draw() override;
    void update() override;
    void destroy() override;

    void place(const int x, const int y);

private:
    std::string font;

    UILabel* title;
    UITextBox* description;

    Power pid;
};
