#include "include/UI/UILabel.h"

#include "include/Window.h"
#include "include/Manager.h"

UILabel::UILabel() {
    rect = {0,0,0,0};
    texture = nullptr;
}

UILabel::UILabel(const std::string& text, const std::string& font, const SDL_Color& color, const int mlength, const bool centered) {
    rect = {0,0,0,0};

    setText(text, font, color, mlength, centered);
}

UILabel::~UILabel() {}

void UILabel::draw() {
    Manager::Draw(texture, nullptr, &rect);
}

void UILabel::destroy() {
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

void UILabel::setText(const std::string& text, const std::string& font, const SDL_Color& color, int mlength, const bool centered) {
    if (mlength < 0) mlength = Window::screen.w;
    
    texture = Manager::GenerateText(
        text,
        Window::manager->getFont(font),
        color,
        mlength,
        centered
    );

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}
