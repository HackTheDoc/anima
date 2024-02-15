#include "include/UI/UIDialogBox.h"

#include "include/Window.h"
#include "include/Manager.h"

UIDialogBox::UIDialogBox(std::string ownerName, std::string text) {
    rect.w = 15 * Window::screen.w / 16;
    rect.h = rect.w / 5;

    owner = Manager::GenerateText(
        (ownerName + " :").c_str(),
        Window::manager->getFont("default bold"),
        hue::font
    );
    SDL_QueryTexture(owner, NULL, NULL, &ownerRect.w, &ownerRect.h);
    
    setText(text);
}

UIDialogBox::~UIDialogBox() {}

void UIDialogBox::draw() {
    Manager::DrawFilledRect(&rect, hue::text_box);

    Manager::Draw(owner, nullptr, &ownerRect);

    if (!haveContent) return;
    
    Manager::Draw(content, nullptr, &contentRect);

    Manager::DrawRect(&rect, hue::border);
}

void UIDialogBox::destroy() {
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
    content = Manager::GenerateText(text.c_str(), Window::manager->getFont("default"), hue::font, rect.w - 2*26);
    SDL_QueryTexture(content, NULL, NULL, &contentRect.w, &contentRect.h);
}

void UIDialogBox::place() {
    rect.x = (Window::screen.w - rect.w) / 2;
    rect.y = Window::screen.h - rect.h - rect.x / 2;

    ownerRect.x = rect.x + 26*(Window::fullscreen+1);
    ownerRect.y = rect.y + 8*(Window::fullscreen+1);

    contentRect.x = rect.x + 26*(Window::fullscreen+1);
    contentRect.y = ownerRect.y + ownerRect.h;
}
