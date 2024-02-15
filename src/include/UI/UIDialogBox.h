#pragma once

#include <string>

#include "UIElement.h"

class UIDialogBox : public UIElement {
public:
    UIDialogBox(std::string ownerName = "", std::string text = "");
    ~UIDialogBox();

    void draw() override;
    void destroy() override;

    void setText(std::string text);
    void place();

private:
    SDL_Rect box;

    SDL_Texture* owner;
    SDL_Rect ownerRect;

    SDL_Texture* content;
    SDL_Rect contentRect;

    bool haveContent;
};
