#include "include/UI/UIDialogBox.h"

#include "include/Window.h"
#include "include/Manager.h"

UIDialogBox::UIDialogBox(std::string ownerName, std::string text) {
    box = Window::manager->getTexture("textbox");
    SDL_QueryTexture(box, NULL, NULL, &boxRect.w, &boxRect.h);
    boxRect.x = boxRect.y = 0;

    float scale = (float)Window::screen.w / (float)boxRect.w;
    if (scale <= 1)
        scale = 1.;

    rect = {0, 0, 0, 0};
    rect.w = boxRect.w * scale;
    rect.h = boxRect.h * scale;

    owner = Manager::GenerateText(
        (ownerName + " :").c_str(),
        Window::manager->getFont("default bold"),
        hue::white
    );
    SDL_QueryTexture(owner, NULL, NULL, &ownerRect.w, &ownerRect.h);
    
    setText(text);
}

UIDialogBox::~UIDialogBox() {}

void UIDialogBox::draw() {
    Manager::Draw(box, &boxRect, &rect);

    Manager::Draw(owner, nullptr, &ownerRect);

    if (!haveContent) return;
    
    Manager::Draw(content, nullptr, &contentRect);
}

void UIDialogBox::destroy() {
    box = nullptr;
    SDL_DestroyTexture(owner);
    SDL_DestroyTexture(content);
}

void UIDialogBox::setText(std::string text) {
    if (text.size() == 0) {
        haveContent = false;
        SDL_DestroyTexture(content);
        return;
    }
    haveContent = true;
    content = Manager::GenerateText(text.c_str(), Window::manager->getFont("default"), rect.w - 2*26, hue::white);
    SDL_QueryTexture(content, NULL, NULL, &contentRect.w, &contentRect.h);
}

void UIDialogBox::placeBottom(int x) {
    if (x == -1) 
        x = (Window::screen.w - rect.w) / 2;

    place(x, Window::screen.h - rect.h - 4*(Window::fullscreen+1));
}

void UIDialogBox::place(int x, int y) {
    rect.x = x;
    rect.y = y;

    ownerRect.x = x + 26*(Window::fullscreen+1);
    ownerRect.y = y + 8*(Window::fullscreen+1);

    contentRect.x = x + 26*(Window::fullscreen+1);
    contentRect.y = ownerRect.y + ownerRect.h;
}
