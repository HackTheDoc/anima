#include "include/WindowStates/IdentityMenu.h"

#include "include/Window.h"
#include "include/Game/Game.h"

IdentityMenu::IdentityMenu() {}

IdentityMenu::~IdentityMenu() {}

void IdentityMenu::init() {
    // create elements
    lbl_title = new UILabel(Text::Get("IDENTITY"), "h1", hue::white);

    std::string n = Game::player->name;
    if (n == "unknown") n = "######";
    lbl_name = new UILabel(n, "big", hue::white);

    lbl_powerLevel = new UILabel(Text::Get("Numen Level: ") + std::to_string(Game::stats.numenLevel), "big", hue::white);

    lbl_attribut = new UILabel(Text::Get("Light Level: ") + std::to_string(Game::stats.attributs), "big", hue::white);

    // create container
    int mw = std::max(std::max(lbl_title->width(), lbl_name->width()), std::max(lbl_powerLevel->width(), lbl_attribut->width()));
    container.w = std::min(Window::screen.w, mw + 128 * (Window::fullscreen + 1));
    container.h = std::min(
        3 * Window::screen.h / 4,
        lbl_title->height() + lbl_name->height() + lbl_powerLevel->height() + lbl_attribut->height() + 5 * 16 * (Window::fullscreen + 1)
    );
    container.x = (Window::screen.w - container.w) / 2;
    container.y = (Window::screen.h - container.h) / 2;

    // placing elements
    lbl_title->place(
        container.x + (container.w - lbl_title->width()) / 2 + 8 * (Window::fullscreen + 1),
        container.y + 16 * (Window::fullscreen + 1)
    );

    lbl_name->place(
        container.x + (container.w - lbl_name->width()) / 2 + 8 * (Window::fullscreen + 1),
        lbl_title->y() + lbl_title->height() + 16 * (Window::fullscreen + 1)
    );

    lbl_powerLevel->place(
        container.x + (container.w - lbl_powerLevel->width()) / 2 + 8 * (Window::fullscreen + 1),
        lbl_name->y() + lbl_name->height() + 16 * (Window::fullscreen + 1)
    );

    lbl_attribut->place(
        container.x + (container.w - lbl_attribut->width()) / 2 + 8 * (Window::fullscreen + 1),
        lbl_powerLevel->y() + lbl_powerLevel->height() + 16 * (Window::fullscreen + 1)
    );
}

void IdentityMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::blur);
    Manager::DrawFilledRect(&container, hue::ui_background);

    lbl_title->draw();
    lbl_name->draw();
    lbl_powerLevel->draw();
    lbl_attribut->draw();

    Manager::DrawRect(&container, hue::border);
}

void IdentityMenu::clean() {
    lbl_title->destroy();
    lbl_name->destroy();
    lbl_powerLevel->destroy();
    lbl_attribut->destroy();
}
