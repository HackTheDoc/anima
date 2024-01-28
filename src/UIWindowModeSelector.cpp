#include "include/UI/UIWindowModeSelector.h"

#include "include/Window.h"

UIWindowModeSelector::UIWindowModeSelector() {
    lbl = new UILabel(Text::Get("Window Mode:"), "default bold", hue::white);

    choice[0] = {SDL_WINDOW_FULLSCREEN_DESKTOP  , new UILabel(Text::Get("Windowed")  , "default", hue::white)};
    choice[1] = {0                              , new UILabel(Text::Get("Fullscreen"), "default", hue::white)};

    reload();
}

UIWindowModeSelector::~UIWindowModeSelector() {}

void UIWindowModeSelector::place(int x, int y) {
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

void UIWindowModeSelector::draw() {
    lbl->draw();
    choice[Window::fullscreen].lbl->draw();
}

void UIWindowModeSelector::update() {
    SDL_Point m;
    SDL_GetMouseState(&m.x, &m.y);

    if (SDL_PointInRect(&m, &selectorRect) && Window::event.mouseClickLeft())
        next();
}

void UIWindowModeSelector::destroy() {
    lbl->destroy();
    for (auto c : choice) {
        c.lbl->destroy();
    }
}

void UIWindowModeSelector::reload() {
    lbl->setText(Text::Get("Window Mode:"), "default bold", hue::white);

    rect = {0,0, lbl->width(), lbl->height()};

    choice[0].lbl->setText(Text::Get("Windowed")  , "default", hue::white);
    rect.w = std::max(rect.w, choice[0].lbl->width());
    rect.h = std::max(rect.h, lbl->height() + choice[0].lbl->height());
    
    choice[1].lbl->setText(Text::Get("Fullscreen"), "default", hue::white);
    rect.w = std::max(rect.w, choice[1].lbl->width());
    rect.h = std::max(rect.h, lbl->height() + choice[1].lbl->height());

    rect.w += 8 *(Window::fullscreen+1); // margin of 4 pixels on left and right
    rect.h += 12*(Window::fullscreen+1); // margin + space between title and choices

    selectorRect = {0,0, rect.w, rect.h - lbl->height()};
}

void UIWindowModeSelector::next() {
    Window::SetWindowMode(choice[Window::fullscreen].id);
}
