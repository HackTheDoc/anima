#include "include/WindowStates/PlayMenu.h"

#include "include/Window.h"

#include "include/Game/Game.h"


UIGameSaveButton* PlayMenu::btn_game[4] = {nullptr, nullptr, nullptr, nullptr};
int PlayMenu::Selection = 0;
UIButton* PlayMenu::btn_load = nullptr;
UIButton* PlayMenu::btn_erase = nullptr;
UIInputField* PlayMenu::input_worldName = nullptr;

PlayMenu::PlayMenu() {}

PlayMenu::~PlayMenu() {}

void PlayMenu::init() {
    /* ----- BACKGROUND ----- */

    gif_background = new UIGifTexture("./assets/animations/main menu", 3, 200, Window::screen);

    /* ----- LABELS ----- */
    lbl_title = new UILabel(Text::Get("Select a world:"), "h2", hue::font, 2 * Window::screen.w / 3);
    lbl_title->place(
        8 * (Window::fullscreen + 1),
        8 * (Window::fullscreen + 1)
    );

    /* ----- BUTTONS ----- */

    const int containerWidth = 2 * Window::screen.w / 3;
    const int offsetY = (Window::screen.h + lbl_title->y() + lbl_title->height()) / 2 - 16 * (Window::fullscreen + 1);

    btn_load = new UIButton(Text::Get("LOAD"), Event::ID::LOAD_SAVE, "h4", hue::font);
    btn_load->place(
        containerWidth - btn_load->width() - 96 * (Window::fullscreen + 1),
        offsetY - btn_load->height() - 8 * (Window::fullscreen + 1)
    );

    btn_erase = new UIButton(Text::Get("ERASE"), Event::ID::ERASE_SAVE, "h4", hue::font);
    btn_erase->place(
        containerWidth - btn_erase->width() - 96 * (Window::fullscreen + 1),
        offsetY + 8 * (Window::fullscreen + 1)
    );

    btn_game[1] = new UIGameSaveButton(Text::Get("World 2"), 2, Event::ID::SELECT_SAVE_2, "h4", hue::font);
    btn_game[1]->place(
        8 * (Window::fullscreen + 1),
        offsetY - btn_game[1]->height() - 8 * (Window::fullscreen + 1)
    );

    btn_game[0] = new UIGameSaveButton(Text::Get("World 1"), 1, Event::ID::SELECT_SAVE_1, "h4", hue::font);
    btn_game[0]->place(
        8 * (Window::fullscreen + 1),
        offsetY - btn_game[1]->height() - btn_game[0]->height() - 24 * (Window::fullscreen + 1));

    btn_game[2] = new UIGameSaveButton(Text::Get("World 3"), 3, Event::ID::SELECT_SAVE_3, "h4", hue::font);
    btn_game[2]->place(
        8 * (Window::fullscreen + 1),
        offsetY + 8 * (Window::fullscreen + 1)
    );

    btn_game[3] = new UIGameSaveButton(Text::Get("World 4"), 4, Event::ID::SELECT_SAVE_4, "h4", hue::font);
    btn_game[3]->place(
        8 * (Window::fullscreen + 1),
        offsetY + btn_game[3]->height() + 24 * (Window::fullscreen + 1));

    btn_quit = new UIButton("X", Event::ID::OPEN_MAIN_MENU, "h3", hue::font);
    btn_quit->place(
        Window::screen.w - btn_quit->width() - 8 * (Window::fullscreen + 1),
        8 * (Window::fullscreen + 1));

    /* ----- world name input ----- */
    input_worldName = new UIInputField(Text::Get("Name the world:"), "Adocia", Event::ID::VALID_WORLD_NAME_INPUT, 16);
    input_worldName->place(
        (Window::screen.w - input_worldName->width()) / 2,
        (Window::screen.h - input_worldName->height()) / 2
    );
}

void PlayMenu::update() {
    gif_background->update();

    if (input_worldName->actived) {
        input_worldName->update();
        return;
    }

    btn_load->update();
    btn_erase->update();

    btn_game[0]->update();
    btn_game[1]->update();
    btn_game[2]->update();
    btn_game[3]->update();

    btn_quit->update();
}

void PlayMenu::render() {
    gif_background->draw();

    lbl_title->draw();

    btn_game[0]->draw();
    btn_game[1]->draw();
    btn_game[2]->draw();
    btn_game[3]->draw();

    btn_quit->draw();

    btn_load->draw();
    btn_erase->draw();

    if (input_worldName->actived)
        input_worldName->draw();
}

void PlayMenu::clean() {
    gif_background->destroy();

    lbl_title->destroy();

    btn_game[0]->destroy();
    btn_game[1]->destroy();
    btn_game[2]->destroy();
    btn_game[3]->destroy();

    btn_quit->destroy();

    btn_load->destroy();
    btn_erase->destroy();

    input_worldName->destroy();
}

bool PlayMenu::IsSelectionActived() {
    return btn_game[PlayMenu::Selection - 1]->isActive();
}

void PlayMenu::RemoveInfos(const int saveID) {
    btn_game[saveID-1]->removeInfos();
}

void PlayMenu::OpenWorldNameInput() {
    input_worldName->actived = true;
}

void PlayMenu::CloseWorldNameInput() {
    input_worldName->actived = false;
}

void PlayMenu::ValidWorldName() {
    if (input_worldName->input.empty())
        Game::stats.worldName = "Adocia";
    else
        Game::stats.worldName = input_worldName->input;
}
