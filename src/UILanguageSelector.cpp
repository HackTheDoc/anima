#include "include/UI/UILanguageSelector.h"

#include "include/Window.h"

UILanguageSelector::UILanguageSelector() {
    lbl = new UILabel(Text::Get("Language:"), "default bold", hue::white);

    choice[0] = {UIChoice::ID::LG_ENGLISH   , new UILabel("English", "default", hue::white)};
    choice[1] = {UIChoice::ID::LG_FRENCH    , new UILabel("French" , "default", hue::white)};

    reload();
}

UILanguageSelector::~UILanguageSelector() {}

void UILanguageSelector::place(int x, int y) {
    rect.x = x;
    rect.y = y;

    selectorRect.x = x;
    selectorRect.y = y + lbl->height();

    lbl->place(
        x + (rect.w - lbl->width()) / 2,
        y + 4*(Window::fullscreen+1)
    );

    for (auto c : choice) {
        c.lbl->place(
            selectorRect.x + (selectorRect.w - c.lbl->width() ) / 2,
            selectorRect.y + (selectorRect.h - c.lbl->height()) / 2
        );
    }
}

void UILanguageSelector::draw() {
    lbl->draw();
    choice[current].lbl->draw();
}

void UILanguageSelector::update() {
    SDL_Point m;
    SDL_GetMouseState(&m.x, &m.y);

    if (SDL_PointInRect(&m, &selectorRect) && Window::event.mouseClickLeft())
        next();
}

void UILanguageSelector::destroy() {
    lbl->destroy();
    for (auto c : choice) {
        c.lbl->destroy();
    }
}

void UILanguageSelector::reload() {
    lbl->setText(Text::Get("Language:"), "default bold", hue::white);

    rect = {0,0, lbl->width(), lbl->height()};

    // English
    choice[0].lbl->setText("English" , "default", hue::white);
    rect.w = std::max(rect.w, choice[0].lbl->width());
    rect.h = std::max(rect.h, lbl->height() + choice[0].lbl->height());
    
    // French
    choice[1].lbl->setText("Français", "default", hue::white);
    rect.w = std::max(rect.w, choice[1].lbl->width());
    rect.h = std::max(rect.h, lbl->height() + choice[1].lbl->height());

    rect.w += 8 *(Window::fullscreen+1); // margin of 4 pixels on left and right
    rect.h += 12*(Window::fullscreen+1); // margin + space between title and choices

    selectorRect = {0,0, rect.w, rect.h - lbl->height()};

    current = Window::language;
}

void UILanguageSelector::next() {
    current++;
    if (current >= choice.size())
        current = 0;
    Window::event.handleSelection((UIChoice::ID)choice[current].id);
}
