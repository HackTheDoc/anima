#include "include/WindowState/IdentityMenu.h"

#include "include/Manager.h"
#include "include/Game/Game.h"

IdentityMenu::IdentityMenu() {}

IdentityMenu::~IdentityMenu() {}

void IdentityMenu::init() {
    // create elements
    title = new UILabel(Text::Get("IDENTITY"), "h1", hue::white);

    std::string n = Game::player->name;
    if (n == "unknown") n = "######";
    name = new UILabel(n, "big", hue::white);

    powerLevel = new UILabel(Text::Get("Numen Level: ") + std::to_string(Game::stats.numenLevel), "big", hue::white);

    attribut = new UILabel(Text::Get("Light Level: ")+std::to_string(Game::stats.attributs), "big", hue::white);

    // create container
    int mw = std::max(std::max(title->width(), name->width()), std::max(powerLevel->width(), attribut->width()));
    container.w = std::min(Window::screen.w, mw + 128 * (Window::fullscreen+1));
    container.h = std::min(
        3 * Window::screen.h / 4, 
        title->height()+name->height()+powerLevel->height()+attribut->height()+5*16*(Window::fullscreen+1)
    );
    container.x = (Window::screen.w - container.w) / 2;
    container.y = (Window::screen.h - container.h) / 2;

    // placing elements
    title->place(
        container.x + (container.w - title->width()) / 2 + 8*(Window::fullscreen+1), 
        container.y + 16*(Window::fullscreen+1)
    );

    name->place(
        container.x + (container.w - name->width()) / 2 + 8*(Window::fullscreen+1),
        title->y() + title->height() + 16*(Window::fullscreen+1)
    );

    powerLevel->place(
        container.x + (container.w - powerLevel->width()) / 2 + 8*(Window::fullscreen+1),
        name->y() + name->height() + 16*(Window::fullscreen+1)
    );

    attribut->place(
        container.x + (container.w - attribut->width()) / 2 + 8*(Window::fullscreen+1),
        powerLevel->y() + powerLevel->height() + 16*(Window::fullscreen+1)
    );
}

void IdentityMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::blur);
    Manager::DrawFilledRect(&container, hue::ui_background);

    title->draw();
    name->draw();
    powerLevel->draw();
    attribut->draw();

    Manager::DrawRect(&container, hue::border);
}

void IdentityMenu::clean() {
    title->destroy();
    name->destroy();
    powerLevel->destroy();
    attribut->destroy();
}
