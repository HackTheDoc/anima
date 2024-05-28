#include "include/WindowStates/PowerMenu.h"

#include "include/Window.h"

PowerMenu::PowerMenu() {}

PowerMenu::~PowerMenu() {}

void PowerMenu::init() {
    numenCounter = new UINumenLevel(
        Window::screen.w / 2,
        Window::screen.h / 2,
        96 * (Window::fullscreen + 1),
        64 * (Window::fullscreen + 1),
        "big"
    );

    lbl_title = new UILabel(Text::Get("Benedictions"), "h3", hue::font);

    const int w = 224 + 112 * Window::fullscreen;
    const int h = 64 + 32 * Window::fullscreen;

    power[Power::BODY_CONTROL] = new UIPowerInfo(Power::BODY_CONTROL, w, h, "default");
    power[Power::BODY_CONTROL]->place(
        numenCounter->x() - numenCounter->width() / 2 - w - 8 * (Window::fullscreen + 1),
        numenCounter->y() - numenCounter->height() / 2 - h - 8 * (Window::fullscreen + 1)
    );

    power[Power::BODY_RESURRECTION] = new UIPowerInfo(Power::BODY_RESURRECTION, w, h, "default");
    power[Power::BODY_RESURRECTION]->place(
        numenCounter->x() + numenCounter->width() / 2 + 8 * (Window::fullscreen + 1),
        numenCounter->y() - numenCounter->height() / 2 - h - 8 * (Window::fullscreen + 1)
    );

    power[Power::BODY_EXPLOSION] = new UIPowerInfo(Power::BODY_EXPLOSION, w, h, "default");
    power[Power::BODY_EXPLOSION]->place(
        numenCounter->x() + numenCounter->width() / 2 + 8 * (Window::fullscreen + 1),
        numenCounter->y() + numenCounter->height() / 2 + 8 * (Window::fullscreen + 1)
    );

    power[Power::SHIELD] = new UIPowerInfo(Power::SHIELD, w, h, "default");
    power[Power::SHIELD]->place(
        numenCounter->x() - numenCounter->width() / 2 - w - 8 * (Window::fullscreen + 1),
        numenCounter->y() + numenCounter->height() / 2 + 8 * (Window::fullscreen + 1)
    );

    container.h = std::max(numenCounter->height() * 2, h + power[SHIELD]->y() - power[BODY_CONTROL]->y());
    container.h += 2 * lbl_title->height() + 16 * (Window::fullscreen + 1);
    container.y = (Window::screen.h - container.h) / 2;

    container.w = 2 * container.h;
    container.x = (Window::screen.w - container.w) / 2;

    lbl_title->place(
        numenCounter->x() - lbl_title->width() / 2,
        container.y + 8 * (Window::fullscreen + 1)
    );
}

void PowerMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::blur);
    Manager::DrawFilledRect(&container, hue::ui_background);

    lbl_title->draw();

    numenCounter->draw();

    power[Power::BODY_RESURRECTION]->draw();
    power[Power::BODY_CONTROL]->draw();
    power[Power::BODY_EXPLOSION]->draw();
    power[Power::SHIELD]->draw();

    Manager::DrawRect(&container, hue::border);
}

void PowerMenu::update() {
    numenCounter->update();

    power[Power::BODY_CONTROL]->update();
    power[Power::BODY_RESURRECTION]->update();
    power[Power::BODY_EXPLOSION]->update();
    power[Power::SHIELD]->update();
}

void PowerMenu::clean() {
    lbl_title->destroy();

    numenCounter->destroy();

    power[Power::BODY_CONTROL]->destroy();
    power[Power::BODY_RESURRECTION]->destroy();
    power[Power::BODY_EXPLOSION]->destroy();
    power[Power::SHIELD]->destroy();
}
