#pragma once

#include <string>

#include "UIElement.h"
#include "UILabel.h"

class UIDialogBox : public UIElement {
public:
    UIDialogBox(const std::string& text, const std::string& ownerName = "");
    ~UIDialogBox();

    void draw() override;
    void destroy() override;

    void setText(const std::string& text);
    void place();

private:
    SDL_Rect box;

    UILabel* lbl_owner;
    UILabel* lbl_content;

    bool haveContent;
};
