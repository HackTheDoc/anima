#include "include/UI/UILanguageSelector.h"

#include "include/Window.h"

UILanguageSelector::UILanguageSelector() {
    lbl_title = new UILabel();

    choice[0] = { Event::ID::SET_LANGUAGE_TO_ENGLISH   , new UILabel()};
    choice[1] = { Event::ID::SET_LANGUAGE_TO_FRENCH    , new UILabel()};

    reload();
}

UILanguageSelector::~UILanguageSelector() {}

void UILanguageSelector::place(const int x, const int y) {
    rect.x = x;
    rect.y = y;

    selectorRect.x = x;
    selectorRect.y = y + lbl_title->height();

    lbl_title->place(
        x + (rect.w - lbl_title->width()) / 2,
        y + 4 * (Window::fullscreen + 1)
    );

    UILabel* lbl = choice[0].second;
    lbl->place(
        selectorRect.x + (selectorRect.w - lbl->width()) / 2,
        selectorRect.y + (selectorRect.h - lbl->height()) / 2
    );

    lbl = choice[1].second;
    lbl->place(
        selectorRect.x + (selectorRect.w - lbl->width()) / 2,
        selectorRect.y + (selectorRect.h - lbl->height()) / 2
    );
}

void UILanguageSelector::draw() {
    lbl_title->draw();
    choice[current].second->draw();
}

void UILanguageSelector::update() {
    SDL_Point m;
    SDL_GetMouseState(&m.x, &m.y);

    if (SDL_PointInRect(&m, &selectorRect) && Window::event.mouseClickLeft())
        next();
}

void UILanguageSelector::destroy() {
    lbl_title->destroy();
    choice[0].second->destroy();
    choice[1].second->destroy();
}

void UILanguageSelector::reload() {
    lbl_title->setText(Text::Get("Language:"), "default bold", hue::font);

    rect = { 0,0, lbl_title->width(), lbl_title->height() };

    // English
    choice[0].second->setText("English", "default", hue::font);
    rect.w = std::max(rect.w, choice[0].second->width());
    rect.h = std::max(rect.h, lbl_title->height() + choice[0].second->height());

    // French
    choice[1].second->setText("Français", "default", hue::font);
    rect.w = std::max(rect.w, choice[1].second->width());
    rect.h = std::max(rect.h, lbl_title->height() + choice[1].second->height());

    rect.w += 8 * (Window::fullscreen + 1); // margin of 4 pixels on left and right
    rect.h += 12 * (Window::fullscreen + 1); // margin + space between title and choices

    selectorRect = { 0,0, rect.w, rect.h - lbl_title->height() };

    current = Window::language;
}

void UILanguageSelector::next() {
    current = !current;
    Window::event.raise(choice[current].first);
}
