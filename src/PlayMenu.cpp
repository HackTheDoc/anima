#include "include/WindowState/PlayMenu.h"

#include "include/Window.h"

#include "include/Game/Game.h"

#include <fstream>
#include <nlohmann/json.hpp>

UIGameSaveButton *PlayMenu::button[4] = {nullptr, nullptr, nullptr, nullptr};
int PlayMenu::Selection = 0;
UIButton *PlayMenu::loadButton = nullptr;
UIButton *PlayMenu::eraseButton = nullptr;
UIInputField* PlayMenu::worldNameInput = nullptr;

PlayMenu::PlayMenu() {}

PlayMenu::~PlayMenu() {}

void PlayMenu::init()
{
    /* ----- BACKGROUND ----- */

    background = new GifTexture("./assets/animations/main menu", 3, 200, Window::screen);

    /* ----- LABELS ----- */
    title = new UILabel(Text::Get("Select a world:"), "h2", hue::white, 2 * Window::screen.w / 3);
    title->place(
        8 * (Window::fullscreen + 1),
        8 * (Window::fullscreen + 1));

    /* ----- BUTTONS ----- */
    int containerWidth = 2 * Window::screen.w / 3;
    int offsetY = (Window::screen.h + title->y() + title->height()) / 2 - 16 * (Window::fullscreen + 1);

    loadButton = new UIButton(Text::Get("LOAD"), UIButton::ID::LOAD_SAVE, "h4", hue::white);
    loadButton->place(
        containerWidth - loadButton->width() - 96 * (Window::fullscreen + 1),
        offsetY - loadButton->height() - 8 * (Window::fullscreen + 1)
    );

    eraseButton = new UIButton(Text::Get("ERASE"), UIButton::ID::ERASE_SAVE, "h4", hue::white);
    eraseButton->place(
        containerWidth - eraseButton->width() - 96 * (Window::fullscreen + 1),
        offsetY + 8 * (Window::fullscreen + 1)
    );

    button[1] = new UIGameSaveButton(Text::Get("World 2"), 2, UIButton::ID::SELECT_SAVE_2, "h4", hue::white);
    button[1]->place(
        8 * (Window::fullscreen + 1),
        offsetY - button[1]->height() - 8 * (Window::fullscreen + 1)
    );

    button[0] = new UIGameSaveButton(Text::Get("World 1"), 1, UIButton::ID::SELECT_SAVE_1, "h4", hue::white);
    button[0]->place(
        8 * (Window::fullscreen + 1),
        offsetY - button[1]->height() - button[0]->height() - 24 * (Window::fullscreen + 1));

    button[2] = new UIGameSaveButton(Text::Get("World 3"), 3, UIButton::ID::SELECT_SAVE_3, "h4", hue::white);
    button[2]->place(
        8 * (Window::fullscreen + 1),
        offsetY + 8 * (Window::fullscreen + 1)
    );

    button[3] = new UIGameSaveButton(Text::Get("World 4"), 4, UIButton::ID::SELECT_SAVE_4, "h4", hue::white);
    button[3]->place(
        8 * (Window::fullscreen + 1),
        offsetY + button[3]->height() + 24 * (Window::fullscreen + 1));

    quitButton = new UIButton("X", UIButton::ID::QUIT_PLAY_MENU, "h3", hue::white);
    quitButton->place(
        Window::screen.w - quitButton->width() - 8 * (Window::fullscreen + 1),
        8 * (Window::fullscreen + 1));

    /* ----- world name input ----- */
    worldNameInput = new UIInputField(Text::Get("Name the world:"), "Adocia", UIButton::ID::VALID_WORLD_NAME_INPUT, 16);
    worldNameInput->place(
        (Window::screen.w - worldNameInput->width()) / 2,
        (Window::screen.h - worldNameInput->height()) / 2
    );
}

void PlayMenu::update()
{
    background->play();

    if (worldNameInput->actived) {
        worldNameInput->update();
        return;
    }

    loadButton->update();
    eraseButton->update();

    button[0]->update();
    button[1]->update();
    button[2]->update();
    button[3]->update();

    quitButton->update();
}

void PlayMenu::render()
{
    background->draw();

    title->draw();

    button[0]->draw();
    button[1]->draw();
    button[2]->draw();
    button[3]->draw();

    quitButton->draw();

    loadButton->draw();
    eraseButton->draw();

    if (worldNameInput->actived) {
        worldNameInput->draw();
    }
}

void PlayMenu::clean()
{
    background->destroy();

    title->destroy();

    button[0]->destroy();
    button[1]->destroy();
    button[2]->destroy();
    button[3]->destroy();

    quitButton->destroy();

    loadButton->destroy();
    eraseButton->destroy();

    worldNameInput->destroy();
}

bool PlayMenu::IsSelectionActived() {
    return button[PlayMenu::Selection - 1]->isActive();
}

void PlayMenu::RemoveInfos(int wid) {
    button[wid-1]->removeInfos();
}

void PlayMenu::OpenWorldNameInput() {
    worldNameInput->actived = true;
}

void PlayMenu::CloseWorldNameInput() {
    worldNameInput->actived = false;
}

void PlayMenu::ValidWorldName() {
    if (worldNameInput->input.empty())
        Game::WorldName = "Adocia";
    else
        Game::WorldName = worldNameInput->input;
}
