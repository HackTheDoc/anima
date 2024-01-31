#include "include/UI/UIButtons.h"

#include "include/Window.h"
#include "include/Manager.h"

UIButton::UIButton() {
    id = UIButton::ID::UNKNOWN;

    texture = nullptr;

    rect = {0, 0, 0, 0};
}

UIButton::UIButton(std::string text, UIButton::ID id, std::string font, const SDL_Color& color) {
    this->id = id;

    setText(text, font, color);

    place(0, 0);
}

UIButton::UIButton(std::string text, int w, int h, UIButton::ID id, std::string font, const SDL_Color& color) {
    this->id = id;

    setText(text, font, color);

    rect.w = w;
    rect.h = h;

    place(0, 0);
}

UIButton::~UIButton() {}

void UIButton::setText(std::string text, std::string font, const SDL_Color& color) {
    texture = Manager::GenerateText(
        text.c_str(),
        Window::manager->getFont(font),
        color);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    hoveredTexture = Manager::GenerateText(
        text.c_str(),
        Window::manager->getFont(font + " bold"),
        color);
    SDL_QueryTexture(hoveredTexture, NULL, NULL, &hoveredTextureRect.w, &hoveredTextureRect.h);
}

void UIButton::setID(UIButton::ID id) {
    this->id = id;
}

UIButton::ID UIButton::getID() {
    return id;
}

void UIButton::place(int x, int y) {
    rect.x = x;
    rect.y = y;

    hoveredTextureRect.x = x + (rect.w - hoveredTextureRect.w) / 2;
    hoveredTextureRect.y = y + (rect.h - hoveredTextureRect.h) / 2;
}

void UIButton::draw() {
    if (hovered)
        Manager::Draw(hoveredTexture, nullptr, &hoveredTextureRect);
    else
        Manager::Draw(texture, nullptr, &rect);
}

void UIButton::update() {
    SDL_Point m;
    SDL_GetMouseState(&m.x, &m.y);

    hovered = SDL_PointInRect(&m, &rect);

    if (hovered && Window::event.mouseClickLeft())
        Window::event.handleButtonClick(id);
}

void UIButton::destroy() {
    SDL_DestroyTexture(texture);
    texture = nullptr;

    SDL_DestroyTexture(hoveredTexture);
    hoveredTexture = nullptr;
}


UILeftCursorButton::UILeftCursorButton(std::string text, UIButton::ID id, std::string font, const SDL_Color& color) {
    this->id = id;

    texture = Manager::GenerateText(
        text.c_str(),
        Window::manager->getFont(font),
        color
    );
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    hoveredTexture = Manager::GenerateText(
        (text + " <").c_str(),
        Window::manager->getFont(font+" bold"),
        color
    );
    SDL_QueryTexture(hoveredTexture, NULL, NULL, &hoveredTextureRect.w, &hoveredTextureRect.h);

    place(0,0);
}

UILeftCursorButton::UILeftCursorButton(std::string text, int w, int h, UIButton::ID id, std::string font, const SDL_Color& color) {
    this->id = id;

    texture = Manager::GenerateText(
        text.c_str(),
        Window::manager->getFont(font),
        color
    );
    rect.w = w;
    rect.h = h;

    hoveredTexture = Manager::GenerateText(
        (text + " <").c_str(),
        Window::manager->getFont(font+" bold"),
        color
    );
    SDL_QueryTexture(hoveredTexture, NULL, NULL, &hoveredTextureRect.w, &hoveredTextureRect.h);

    place(0,0);
}

UILeftCursorButton::~UILeftCursorButton() {}

void UILeftCursorButton::place(int x, int y) {
    rect.x = x;
    rect.y = y;

    hoveredTextureRect.x = x;
    hoveredTextureRect.y = y;
}

UIDoubleCursorButton::UIDoubleCursorButton(std::string text, UIButton::ID id, std::string font, const SDL_Color& color) {
    this->id = id;

    texture = Manager::GenerateText(
        text.c_str(),
        Window::manager->getFont(font),
        color
    );
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    hoveredTexture = Manager::GenerateText(
        ("> "+text+" <").c_str(),
        Window::manager->getFont(font+" bold"),
        color
    );
    SDL_QueryTexture(hoveredTexture, NULL, NULL, &hoveredTextureRect.w, &hoveredTextureRect.h);

    place(0,0);
}

UIDoubleCursorButton::UIDoubleCursorButton(std::string text, int w, int h, UIButton::ID id, std::string font, const SDL_Color& color) {
    this->id = id;

    texture = Manager::GenerateText(
        text.c_str(),
        Window::manager->getFont(font),
        color
    );
    rect.w = w;
    rect.h = h;

    hoveredTexture = Manager::GenerateText(
        ("> "+text+" <").c_str(),
        Window::manager->getFont(font+" bold"),
        color
    );
    SDL_QueryTexture(hoveredTexture, NULL, NULL, &hoveredTextureRect.w, &hoveredTextureRect.h);

    place(0,0);
}

UIDoubleCursorButton::~UIDoubleCursorButton() {}
