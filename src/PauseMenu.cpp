#include "include/WindowState/PauseMenu.h"

#include "include/Window.h"
#include "include/Manager.h"

PauseMenu::PauseMenu() {}

PauseMenu::~PauseMenu() {}

void PauseMenu::init() {
    // create elements
    label = new UILabel("PAUSE", "h1", hue::font);

    button[SAVE] = new UIDoubleCursorButton(Text::Get("SAVE"), UIButton::ID::SAVE_GAME, "h3", hue::font);
    button[RESUME] = new UIDoubleCursorButton(Text::Get("RESUME"), UIButton::ID::RESUME_GAME, "h3", hue::font);
    button[QUIT] = new UIDoubleCursorButton(Text::Get("QUIT"), UIButton::ID::QUIT_GAME, "h3", hue::font);
    
    // create container
    int mw = std::max(std::max(label->width(), button[SAVE]->width()), std::max(button[RESUME]->width(), button[QUIT]->width()));
    container.w = std::min(Window::screen.w, mw + 128*(Window::fullscreen+1));
    container.h = Window::screen.h * 0.75;
    container.x = (Window::screen.w - container.w) / 2;
    container.y = (Window::screen.h - container.h) / 2;

    
    // place title
    label->place(
        container.x + (container.w - label->width()) / 2 + 8*(Window::fullscreen+1), 
        container.y    
    );

    // place buttons
    int offsetY = container.y + (container.h + label->height()) / 2;

    button[SAVE]->place(
        container.x + (container.w - button[SAVE]->width()) / 2,
        offsetY - (button[SAVE]->height() / 2)
    );

    button[RESUME]->place(
        container.x + (container.w - button[RESUME]->width()) / 2,
        (Window::screen.h + label->y() + label->height() - button[SAVE]->y()) / 2
    );

    button[QUIT]->place(
        container.x + (container.w - button[QUIT]->width()) / 2,
        (container.y + container.h + button[SAVE]->y() + button[SAVE]->height() - button[QUIT]->height()) / 2
    );
}

void PauseMenu::update() {
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
        button[i]->update();
    }
}

void PauseMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::blur);
    Manager::DrawFilledRect(&container, hue::ui_background);

    for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
        button[i]->draw();
    }

    label->draw();

    Manager::DrawRect(&container, hue::border); 
}

void PauseMenu::clean() {
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
        button[i]->destroy();
    }

    label->destroy();
}
