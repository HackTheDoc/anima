#include "include/UI/UIButton.h"

#include "include/Window.h"

UIButton::UIButton() {
    eid = Event::ID::UNKNOWN;
    type = Type::DEFAULT;

    texture = nullptr;
    rect = { 0, 0, 0, 0 };

    hovered = false;
    hoveredTexture = nullptr;
    hoveredTextureRect = { 0, 0, 0, 0 };
}

UIButton::UIButton(const std::string& text, const Event::ID id, const std::string& font, const SDL_Color& color, const Type type) {
    setID(id);
    this->type = type;

    setText(text, font, color);

    place(0, 0);

    hovered = false;
}

UIButton::~UIButton() {}

void UIButton::setText(const std::string& text, const std::string& font, const SDL_Color& color) {
    texture = Manager::GenerateText(
        text,
        font,
        color);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    std::string t;
    switch (type) {
    case Type::LEFT_CURSOR:
        t = "> " + text;
        break;
    case Type::RIGHT_CURSOR:
        t = text + " <";
        break;
    case Type::DOUBLE_CURSOR:
        t = "> " + text + " <";
        break;
    case Type::DEFAULT:
    default:
        t = text;
        break;
    }
    hoveredTexture = Manager::GenerateText(
        t,
        font + " bold",
        color);
    SDL_QueryTexture(hoveredTexture, NULL, NULL, &hoveredTextureRect.w, &hoveredTextureRect.h);
}

void UIButton::setID(const Event::ID eid) {
    this->eid = eid;
}

Event::ID UIButton::getID() {
    return eid;
}

void UIButton::place(const int x, const int y) {
    rect.x = x;
    rect.y = y;

    if (type == Type::RIGHT_CURSOR) {
        hoveredTextureRect.x = x;
        hoveredTextureRect.y = y;
    }
    else {
        hoveredTextureRect.x = x + (rect.w - hoveredTextureRect.w) / 2;
        hoveredTextureRect.y = y + (rect.h - hoveredTextureRect.h) / 2;
    }
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
        Window::event.raise(eid);
}

void UIButton::destroy() {
    SDL_DestroyTexture(texture);
    texture = nullptr;

    SDL_DestroyTexture(hoveredTexture);
    hoveredTexture = nullptr;
}
