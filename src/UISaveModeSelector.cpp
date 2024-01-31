#include "include/UI/UISaveModeSelector.h"

#include "include/Window.h"
#include "include/Manager.h"
#include "include/Save.h"

UISaveModeSelector::UISaveModeSelector() {
    title = new UILabel(Text::Get("Save Mode:"), "default bold", hue::white);

    value = new UILabel(Text::Get(vstring[Save::Auto]), "default", hue::white);

    rect.w = title->width() + value->width() + 4*(Window::fullscreen+1);
    rect.h = std::max(title->height(), value->height());

    place(0,0);
}

UISaveModeSelector::~UISaveModeSelector() {}

void UISaveModeSelector::draw() {
    title->draw();
    value->draw();
}

void UISaveModeSelector::update() {
    SDL_Point m;
    SDL_GetMouseState(&m.x, &m.y);
    if (SDL_PointInRect(&m, &rect) && Window::event.mouseClickLeft()) {
        Save::Auto = !Save::Auto;

        value->setText(Text::Get(vstring[Save::Auto]), "default", hue::white);
        value->place(
            title->x() + title->width() + 4*(Window::fullscreen+1),
            rect.y + (rect.h - value->height()) / 2
        );

        Window::SaveConfig();
    }
}

void UISaveModeSelector::destroy() {
    title->destroy();
    value->destroy();
}

void UISaveModeSelector::place(int x, int y) {
    rect.x = x;
    rect.y = y;

    title->place(
        x,
        y + (rect.h - title->height()) / 2
    );

    value->place(
            title->x() + title->width() + 4*(Window::fullscreen+1),
        y + (rect.h - value->height()) / 2
    );
}

void UISaveModeSelector::reload() {
    title->setText(Text::Get("Save Mode:"), "default bold", hue::white);

    value->setText(Text::Get(vstring[Save::Auto]), "default", hue::white);

    rect.w = title->width() + value->width() + 4*(Window::fullscreen+1);
    rect.h = std::max(title->height(), value->height());
}
