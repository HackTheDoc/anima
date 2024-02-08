#include "include/WindowState/DeathMenu.h"

#include "include/Window.h"
#include "include/Manager.h"

DeathMenu::DeathMenu() {}

DeathMenu::~DeathMenu() {}

void DeathMenu::init() {
    title = new UILabel("YOU HAVE DIED", "h1", hue::white);
    btn_load = new UIDoubleCursorButton("LOAD LAST SAVE", UIButton::ID::LOAD_LAST_SAVE, "h3", hue::white);
    btn_quit = new UIDoubleCursorButton("QUIT GAME", UIButton::ID::QUIT_GAME, "h3", hue::white);

    const int yoff = 3* Window::screen.h / 4;
    title->place(
        (Window::screen.w - title->width()) / 2,
        (yoff  - title->height()) / 2
    );

    const int span = 8*(Window::fullscreen+1);
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

    title->draw();
    btn_load->draw();
    btn_quit->draw();
}

void DeathMenu::clean() {
    title->destroy();
    btn_load->destroy();
    btn_quit->destroy();
}
