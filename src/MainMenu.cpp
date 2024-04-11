#include "include/WindowStates/MainMenu.h"

#include "include/Window.h"

MainMenu::MainMenu() {}

MainMenu::~MainMenu() {}

void MainMenu::init() {
    /* ----- BACKGROUND ----- */

    gif_background = new UIGifTexture("./assets/animations/main menu", 3, 200, Window::screen);

    /* ----- LABELS ----- */

    lbl_title = new UILabel(Window::TITLE, "h1", hue::font);
    lbl_title->place(8 * (Window::fullscreen + 1), 0);

    lbl_version = new UILabel("v0.1", "default", hue::font);
    lbl_version->place(
        Window::screen.w - lbl_version->width() - 8 * (Window::fullscreen + 1),
        8 * (Window::fullscreen + 1)
    );

    /* ----- BUTTONS ----- */

    const int offsetY = (Window::screen.h + lbl_title->height()) / 2;

    btn_options = new UIButton(Text::Get("Options"), Event::ID::OPEN_OPTIONS, "h3", hue::font, UIButton::Type::RIGHT_CURSOR);
    btn_options->place(
        16 * (Window::fullscreen + 1),
        offsetY - btn_options->height() - 8 * (Window::fullscreen + 1)
    );

    btn_play = new UIButton(Text::Get("Play"), Event::ID::OPEN_PLAY_MENU, "h3", hue::font, UIButton::Type::RIGHT_CURSOR);
    btn_play->place(
        16 * (Window::fullscreen + 1),
        offsetY - btn_options->height() - btn_play->height() - 24 * (Window::fullscreen + 1)
    );

    btn_credits = new UIButton(Text::Get("Credits"), Event::ID::OPEN_CREDITS, "h3", hue::font, UIButton::Type::RIGHT_CURSOR);
    btn_credits->place(
        16 * (Window::fullscreen + 1),
        offsetY + 8 * (Window::fullscreen + 1)
    );

    btn_quit = new UIButton(Text::Get("Quit"), Event::ID::QUIT, "h3", hue::font, UIButton::Type::RIGHT_CURSOR);
    btn_quit->place(
        16 * (Window::fullscreen + 1),
        offsetY + btn_credits->height() + 24 * (Window::fullscreen + 1)
    );
}

void MainMenu::update() {
    gif_background->update();

    btn_play->update();
    btn_options->update();
    btn_credits->update();
    btn_quit->update();
}

void MainMenu::render() {
    gif_background->draw();

    btn_play->draw();
    btn_options->draw();
    btn_credits->draw();
    btn_quit->draw();

    lbl_title->draw();
    lbl_version->draw();
}

void MainMenu::clean() {
    gif_background->destroy();

    btn_play->destroy();
    btn_options->destroy();
    btn_credits->destroy();
    btn_quit->destroy();

    lbl_title->destroy();
    lbl_version->destroy();
}
