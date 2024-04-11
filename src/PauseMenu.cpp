#include "include/WindowStates/PauseMenu.h"

#include "include/Window.h"

PauseMenu::PauseMenu() {}

PauseMenu::~PauseMenu() {}

void PauseMenu::init() {
    // create elements
    lbl_title = new UILabel("PAUSE", "h1", hue::font);

    btn_save = new UIButton(Text::Get("SAVE"), Event::ID::SAVE_GAME, "h3", hue::font, UIButton::Type::DOUBLE_CURSOR);
    btn_resume = new UIButton(Text::Get("RESUME"), Event::ID::RESUME_GAME, "h3", hue::font, UIButton::Type::DOUBLE_CURSOR);
    btn_quit = new UIButton(Text::Get("QUIT"), Event::ID::QUIT_GAME, "h3", hue::font, UIButton::Type::DOUBLE_CURSOR);

    // create container
    const int mw = std::max(std::max(lbl_title->width(), btn_save->width()), std::max(btn_resume->width(), btn_quit->width()));
    container.w = std::min(Window::screen.w, mw + 128 * (Window::fullscreen + 1));
    container.h = Window::screen.h * 0.75;
    container.x = (Window::screen.w - container.w) / 2;
    container.y = (Window::screen.h - container.h) / 2;


    // place title
    lbl_title->place(
        container.x + (container.w - lbl_title->width()) / 2 + 8 * (Window::fullscreen + 1),
        container.y
    );

    // place buttons
    const int offsetY = container.y + (container.h + lbl_title->height()) / 2;

    btn_save->place(
        container.x + (container.w - btn_save->width()) / 2,
        offsetY - (btn_save->height() / 2)
    );

    btn_resume->place(
        container.x + (container.w - btn_resume->width()) / 2,
        (Window::screen.h + lbl_title->y() + lbl_title->height() - btn_save->y()) / 2
    );

    btn_quit->place(
        container.x + (container.w - btn_quit->width()) / 2,
        (container.y + container.h + btn_save->y() + btn_save->height() - btn_quit->height()) / 2
    );
}

void PauseMenu::update() {
    btn_save->update();
    btn_resume->update();
    btn_quit->update();
}

void PauseMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::blur);
    Manager::DrawFilledRect(&container, hue::ui_background);

    btn_save->draw();
    btn_resume->draw();
    btn_quit->draw();

    lbl_title->draw();

    Manager::DrawRect(&container, hue::border);
}

void PauseMenu::clean() {
    btn_save->destroy();
    btn_resume->destroy();
    btn_quit->destroy();

    lbl_title->destroy();
}
