#include "include/WindowStates/DeathMenu.h"

#include "include/Window.h"

DeathMenu::DeathMenu() {}

DeathMenu::~DeathMenu() {}

void DeathMenu::init() {
    lbl_title = new UILabel("YOU HAVE DIED", "h1", hue::font);

    btn_load = new UIButton("LOAD LAST SAVE", Event::ID::LOAD_LAST_SAVE, "h3", hue::font, UIButton::Type::DOUBLE_CURSOR);
    btn_quit = new UIButton("QUIT GAME", Event::ID::QUIT_GAME, "h3", hue::font, UIButton::Type::DOUBLE_CURSOR);

    const int yoff = 3 * Window::screen.h / 4;
    lbl_title->place(
        (Window::screen.w - lbl_title->width()) / 2,
        (yoff - lbl_title->height()) / 2
    );

    const int span = 8 * (Window::fullscreen + 1);
    btn_load->place(
        (Window::screen.w - btn_load->width()) / 2,
        yoff - btn_load->height() - span
    );

    btn_quit->place(
        (Window::screen.w - btn_quit->width()) / 2,
        yoff + span
    );

}

void DeathMenu::update() {
    btn_load->update();
    btn_quit->update();
}

void DeathMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::blur_red);

    lbl_title->draw();
    btn_load->draw();
    btn_quit->draw();
}

void DeathMenu::clean() {
    lbl_title->destroy();
    btn_load->destroy();
    btn_quit->destroy();
}
