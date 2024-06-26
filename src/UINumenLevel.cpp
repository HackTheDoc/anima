#include "include/UI/UINumenLevel.h"

#include "include/Window.h"
#include "include/Game/Game.h"

UINumenLevel::UINumenLevel(const int x, const int y, const int w, const int h, const std::string& font) {
    rect = { x,y,w,h };

    this->font = font;

    lbl = new UILabel("0", font, hue::font);

    doc = new UILabel(Text::Get("Numen tokens"), font, hue::font);
    docRect.w = doc->width() + 8 * (Window::fullscreen + 1);
    docRect.h = doc->height() + 8 * (Window::fullscreen + 1);
}

UINumenLevel::~UINumenLevel() {}

void UINumenLevel::draw() {
    lbl->draw();

    Manager::DrawLosange(rect.x, rect.y, rect.w, rect.h, hue::border);

    int x, y;
    SDL_GetMouseState(&x, &y);

    if (std::abs(x - rect.x) <= lbl->width() && std::abs(y - rect.y) <= lbl->height()) {
        doc->place(x, y);
        docRect.x = x - 4 * (Window::fullscreen + 1);
        docRect.y = y - 4 * (Window::fullscreen + 1);
        Manager::DrawFilledRect(&docRect, hue::ui_background);
        doc->draw();
        Manager::DrawRect(&docRect, hue::border);
    }
}

void UINumenLevel::update() {
    lbl->setText(std::to_string(Game::player->numenLevel), font, hue::font);
    lbl->place(
        rect.x - lbl->width() / 2,
        rect.y - lbl->height() / 2
    );
}

void UINumenLevel::destroy() {
    lbl->destroy();

    doc->destroy();
}
