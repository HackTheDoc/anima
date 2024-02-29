#include "include/WindowState/MainMenu.h"

#include "include/Window.h"

MainMenu::MainMenu() {}

MainMenu::~MainMenu() {}

void MainMenu::init() {
    /* ----- BACKGROUND ----- */

    background = new GifTexture("./assets/animations/main menu", 3, 200, Window::screen);

    /* ----- LABELS ----- */

    label[TITLE] = new UILabel(Window::title, "h1", hue::font);
    label[TITLE]->place(8*(Window::fullscreen+1), 0);

    label[VERSION] = new UILabel("v0.1", "default", hue::font);
    label[VERSION]->place(
        Window::screen.w - label[VERSION]->width() - 8*(Window::fullscreen+1),
        8*(Window::fullscreen+1)
    );

    /* ----- BUTTONS ----- */
    int offsetY = (Window::screen.h + label[TITLE]->height()) / 2;


    button[OPTIONS] = new UILeftCursorButton(Text::Get("Options"), UIButton::ID::OPTIONS, "h3", hue::font);
    button[OPTIONS]->place(
        16*(Window::fullscreen+1),
        offsetY - button[OPTIONS]->height() - 8*(Window::fullscreen+1)
    );

    button[PLAY] = new UILeftCursorButton(Text::Get("Play"), UIButton::ID::PLAY, "h3", hue::font);
    button[PLAY]->place(
        16*(Window::fullscreen+1),
        offsetY - button[OPTIONS]->height() - button[PLAY]->height() - 24*(Window::fullscreen+1)
    );

    button[CREDITS] = new UILeftCursorButton(Text::Get("Credits"), UIButton::ID::CREDITS, "h3", hue::font);
    button[CREDITS]->place(
        16*(Window::fullscreen+1),
        offsetY + 8*(Window::fullscreen+1)
    );

    button[QUIT] = new UILeftCursorButton(Text::Get("Quit"), UIButton::ID::QUIT, "h3", hue::font);
    button[QUIT]->place(
        16*(Window::fullscreen+1),
        offsetY + button[CREDITS]->height() + 24*(Window::fullscreen+1)
    );
}

void MainMenu::update() {
    background->play();

    for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
        button[i]->update();
    }
}

void MainMenu::render() {
    background->draw();
    
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
        button[i]->draw();
    }

    for (int i = 0; i < NUMBER_OF_LABELS; i++) {
        label[i]->draw();
    }
}

void MainMenu::clean() {
    background->destroy();

    for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
        button[i]->destroy();
    }

    for (int i = 0; i < NUMBER_OF_LABELS; i++) {
        label[i]->destroy();
    }
}
