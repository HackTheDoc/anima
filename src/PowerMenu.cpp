#include "include/WindowState/PowerMenu.h"

#include "include/Window.h"

PowerMenu::PowerMenu() {}

PowerMenu::~PowerMenu() {}

void PowerMenu::init() {
    numenCounter = new UINumenLevel(
        Window::screen.w / 2, 
        Window::screen.h / 2, 
        96*(Window::fullscreen+1),
        64*(Window::fullscreen+1),
        "big"
    );

    title = new UILabel(Text::Get("Benedictions"), "h3", hue::white);

    int w = 224 + 112 * Window::fullscreen;
    int h = 64  + 32  * Window::fullscreen;

    power[Power::BODY_CONTROL] = new UIPowerInfo(Power::BODY_CONTROL, w, h, "default");
    power[Power::BODY_CONTROL]->place(
        numenCounter->x() - numenCounter->width() / 2 - w - 8*(Window::fullscreen+1),
        numenCounter->y() - numenCounter->height() / 2 - h - 8*(Window::fullscreen+1)
    );

    power[Power::BODY_RESURRECTION] = new UIPowerInfo(Power::BODY_RESURRECTION, w, h, "default");
    power[Power::BODY_RESURRECTION]->place(
        numenCounter->x() + numenCounter->width() / 2 + 8*(Window::fullscreen+1),
        numenCounter->y() - numenCounter->height() / 2 - h - 8*(Window::fullscreen+1)
    );
    
    power[Power::BODY_EXPLOSION] = new UIPowerInfo(Power::BODY_EXPLOSION, w, h, "default");
    power[Power::BODY_EXPLOSION]->place(
        numenCounter->x() + numenCounter->width() / 2 + 8*(Window::fullscreen+1),
        numenCounter->y() + numenCounter->height() / 2 + 8*(Window::fullscreen+1)
    );
    
    power[Power::SHIELD] = new UIPowerInfo(Power::SHIELD, w, h, "default");
    power[Power::SHIELD]->place(
        numenCounter->x() - numenCounter->width() / 2 - w - 8*(Window::fullscreen+1),
        numenCounter->y() + numenCounter->height() / 2 + 8*(Window::fullscreen+1)
    );
    
    container.h = std::max(numenCounter->height() * 2, h + power[SHIELD]->y() - power[BODY_CONTROL]->y());
    container.h += 2 * title->height() + 16*(Window::fullscreen+1);
    container.y = (Window::screen.h - container.h) / 2;

    container.w = 2 * container.h;
    container.x = (Window::screen.w - container.w) / 2;

    title->place(
        numenCounter->x() - title->width() / 2,
        container.y + 8*(Window::fullscreen+1)
    );
}

void PowerMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::blur);
    Manager::DrawFilledRect(&container, hue::ui_background);

    title->draw();

    numenCounter->draw();
    
    power[Power::BODY_CONTROL]->draw();
    power[Power::BODY_RESURRECTION]->draw();
    power[Power::BODY_EXPLOSION]->draw();
    power[Power::SHIELD]->draw();

   Manager::DrawRect(&container, hue::white);
}

void PowerMenu::update() {
    numenCounter->update();

    power[Power::BODY_CONTROL]->update();
    power[Power::BODY_RESURRECTION]->update();
    power[Power::BODY_EXPLOSION]->update();
    power[Power::SHIELD]->update();
}

void PowerMenu::clean() {
    title->destroy();

    numenCounter->destroy();

    power[Power::BODY_CONTROL]->destroy();
    power[Power::BODY_RESURRECTION]->destroy();
    power[Power::BODY_EXPLOSION]->destroy();
    power[Power::SHIELD]->destroy();
}
