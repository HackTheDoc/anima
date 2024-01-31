#include "include/UI/UILabel.h"

#include "include/Window.h"
#include "include/Manager.h"

UILabel::UILabel(std::string text, std::string font, const SDL_Color& color) {
    rect.x = rect.y = 0;

    setText(text, font, color);
}

UILabel::UILabel(std::string text, std::string font, const SDL_Color& color, int mlength) {
    rect.x = rect.y = 0;

    setText(text, font, color, mlength);
}

UILabel::~UILabel() {}

void UILabel::draw() {
    Manager::Draw(texture, nullptr, &rect);
}

void UILabel::destroy() {
    SDL_DestroyTexture(texture);
    texture = nullptr;
}

void UILabel::setText(std::string text, std::string font, const SDL_Color& color) {
    texture = Manager::GenerateText(
        text.c_str(),
        Window::manager->getFont(font),
        color
    );

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}

void UILabel::setText(std::string text, std::string font, const SDL_Color& color, int mlength) {
    texture = Manager::GenerateText(
        text.c_str(),
        Window::manager->getFont(font),
        color,
        mlength
    );

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
}
