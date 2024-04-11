#include "include/Event.h"

#include "include/Game/Game.h"

#include "include/Window.h"

#include "include/WindowStates/PlayMenu.h"

#include "include/Save.h"
#include "include/KeyMap.h"

#include <iostream>

std::string to_string(const Event::ID eid) {
    switch (KeyMap::GetKeyCode(eid)) {
    case SDLK_a:
        return "A";
    case SDLK_b:
        return "B";
    case SDLK_c:
        return "C";
    case SDLK_d:
        return "D";
    case SDLK_e:
        return "E";
    case SDLK_f:
        return "F";
    case SDLK_g:
        return "G";
    case SDLK_h:
        return "H";
    case SDLK_i:
        return "I";
    case SDLK_j:
        return "J";
    case SDLK_k:
        return "K";
    case SDLK_l:
        return "L";
    case SDLK_m:
        return "M";
    case SDLK_n:
        return "N";
    case SDLK_o:
        return "O";
    case SDLK_p:
        return "P";
    case SDLK_q:
        return "Q";
    case SDLK_r:
        return "R";
    case SDLK_s:
        return "S";
    case SDLK_t:
        return "T";
    case SDLK_u:
        return "U";
    case SDLK_v:
        return "V";
    case SDLK_w:
        return "W";
    case SDLK_x:
        return "X";
    case SDLK_y:
        return "Y";
    case SDLK_z:
        return "Z";

    case SDLK_UP:
        return Text::Get("UP");
    case SDLK_DOWN:
        return Text::Get("DOWN");
    case SDLK_LEFT:
        return Text::Get("LEFT");
    case SDLK_RIGHT:
        return Text::Get("RIGHT");

    case SDLK_RALT:
    case SDLK_LALT:
        return "ALT";
    case SDLK_ESCAPE:
        return "ESC";
    case SDLK_RETURN:
        return Text::Get("ENTER");
    case SDLK_RCTRL:
        return "RCTRL";
    case SDLK_LCTRL:
        return "LCTRL";
    case SDLK_RSHIFT:
        return "RSHIFT";
    case SDLK_LSHIFT:
        return "LSHIFT";
    case SDLK_CAPSLOCK:
        return "CAPS";
    case SDLK_TAB:
        return "TAB";

    case SDLK_0:
        return "0";
    case SDLK_1:
        return "1";
    case SDLK_2:
        return "2";
    case SDLK_3:
        return "3";
    case SDLK_4:
        return "4";
    case SDLK_5:
        return "5";
    case SDLK_6:
        return "6";
    case SDLK_7:
        return "7";
    case SDLK_8:
        return "8";
    case SDLK_9:
        return "9";
    default:
        return "";
    }
}

Event::Event() {}

Event::~Event() {}

void Event::linkTo(Window* w) {
    window = w;
}

void Event::handleKeyboardInputs() {
    switch (Window::manager->getCurrentStateID()) {
    case WindowState::Type::MAIN:
        handleMainMenuEvents();
        break;
    case WindowState::Type::OPTIONS_MENU:
        handleOptionsMenuEvents();
        break;
    case WindowState::Type::CREDITS:
        handleCreditsEvents();
        break;
    case WindowState::Type::CINEMATIC:
        handleCinematicEvents();
        break;
    case WindowState::Type::GAME:
        handleGameEvents();
        break;
    case WindowState::Type::PAUSE_MENU:
        handlePauseMenuEvents();
        break;
    case WindowState::Type::POWER_MENU:
        handlePowerMenuEvents();
        break;
    case WindowState::Type::INVENTORY_MENU:
        handleInventoryMenuEvents();
        break;
    case WindowState::Type::QUEST_MENU:
        handleQuestMenuEvents();
        break;
    case WindowState::Type::DEATH_MENU:
        handleDeathMenuEvents();
        break;
    case WindowState::Type::IDENTITY_MENU:
        handleIdentityMenuEvents();
        break;
    case WindowState::Type::UNKNOWN:
    default:
        break;
    }
}

bool Event::mouseClickLeft() {
    return e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT;
}

bool Event::mouseClickRight() {
    return e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT;
}

bool Event::raised(const Event::ID id) {
    if (e.type != SDL_KEYUP) return false;

    SDL_KeyCode k = SDL_KeyCode(e.key.keysym.sym);
    return KeyMap::Key[k] == id;
}

void Event::raise(const Event::ID id) {
    switch (id) {
    case SET_LANGUAGE_TO_ENGLISH:
        Window::SetLanguage(Language::ENGLISH);
        break;
    case SET_LANGUAGE_TO_FRENCH:
        Window::SetLanguage(Language::FRENCH);
        break;
    case SET_WINDOW_TO_FULLSCREEN:
        Window::SetWindowMode(SDL_WINDOW_FULLSCREEN_DESKTOP);
        break;
    case SET_WINDOW_TO_DEFAULT:
        Window::SetWindowMode(0);
        break;
    case QUIT:
        Window::isRunning = false;
        break;
    case OPEN_MAIN_MENU:
        window->openMainMenu();
        break;
    case OPEN_OPTIONS:
        window->openOptionsMenu();
        break;
    case OPEN_GENERAL_SETTINGS:
        window->openGeneralOptions();
        break;
    case OPEN_CONTROLS_SETTINGS:
        window->openControlsOptions();
        break;
    case OPEN_CREDITS:
        window->openCredits();
        break;
    case OPEN_PLAY_MENU:
        window->openPlayMenu();
        break;
    case LOAD_SAVE:
        if (PlayMenu::IsSelectionActived()) {
            if (!Save::Exist(PlayMenu::Selection))
                PlayMenu::OpenWorldNameInput();
            else
                window->openGame(PlayMenu::Selection);
        }
        break;
    case ERASE_SAVE:
        if (PlayMenu::IsSelectionActived())
            PlayMenu::RemoveInfos(PlayMenu::Selection);
        Save::Erase(PlayMenu::Selection);
        break;
    case SELECT_SAVE_1:
        PlayMenu::Selection = 1;
        break;
    case SELECT_SAVE_2:
        PlayMenu::Selection = 2;
        break;
    case SELECT_SAVE_3:
        PlayMenu::Selection = 3;
        break;
    case SELECT_SAVE_4:
        PlayMenu::Selection = 4;
        break;
    case VALID_WORLD_NAME_INPUT:
        PlayMenu::ValidWorldName();
        window->openGame(PlayMenu::Selection);
        break;
    case QUIT_INPUT_FIELD:
        PlayMenu::CloseWorldNameInput();
        break;
    case QUIT_GAME:
        window->quitGame();
        break;
    case SAVE_GAME:
        Save::Update(Game::WorldID);
        break;
    case LOAD_LAST_SAVE:
        window->loadLastGameSave();
        break;
    case RESUME_GAME:
        window->resumeGame();
        break;
    case PAUSE:
        window->pauseGame();
        break;
    case OPEN_INVENTORY:
        Tutorial::Complete(Tutorial::Step::OPEN_INVENTORY);
        window->openInventory(Game::player->parseInventory(true));
        break;
    case OPEN_POWER_MENU:
        Tutorial::Complete(Tutorial::Step::OPEN_BENEDICTIONS);
        window->openPowerMenu();
        break;
    case OPEN_QUEST_MENU:
        Tutorial::Complete(Tutorial::Step::OPEN_QUESTS);
        window->openQuestMenu();
        break;
    case OPEN_IDENTITY_MENU:
        window->openIdentityMenu();
        break;
    case OPEN_PLAYER_DEATH_MENU:
        window->openDeathMenu();
        break;
    default:
        break;
    }
}

void Event::handleMainMenuEvents() {
    if (e.type != SDL_KEYUP || !(SDL_GetModState() & KMOD_CTRL))
        return;
    switch (e.key.keysym.sym) {
    case SDLK_q:
        Window::isRunning = false;
        break;
    case SDLK_r:
        window->openMainMenu();
        break;
#ifdef DEV_MOD
    case SDLK_e:
        Save::Erase(4);
        window->openGame(4);
        Game::player->unlockPower(Power::BODY_RESURRECTION);
        Game::player->unlockPower(Power::BODY_EXPLOSION);
        Game::player->unlockPower(Power::SHIELD);
        Game::player->modifyNumenLevelBy(+10);
        window->quitGame();
        std::cout << "initialized world 4 for dev usage" << std::endl;
        window->openGame(4);
        break;
    case SDLK_p:
        window->openGame(4);
        break;
#else
    case SDLK_p:
        window->openPlayMenu();
        break;
#endif
    case SDLK_o:
        window->openOptionsMenu();
        break;
    case SDLK_c:
        window->openCredits();
        break;
    default:
        break;
    }
}

void Event::handleOptionsMenuEvents() {
    if (e.type != SDL_KEYUP || !(SDL_GetModState() & KMOD_CTRL))
        return;

    switch (e.key.keysym.sym) {
    case SDLK_q:
        window->openMainMenu();
        break;
    default:
        break;
    }
}

void Event::handleCreditsEvents() {
    if (e.type != SDL_KEYUP || !(SDL_GetModState() & KMOD_CTRL))
        return;

    switch (e.key.keysym.sym) {
    case SDLK_q:
        window->openMainMenu();
        break;
    default:
        break;
    }
}

void Event::handleCinematicEvents() {
    if (e.type != SDL_KEYUP) return;

    switch (e.key.keysym.sym) {
    case SDLK_SPACE:
    case SDLK_RETURN:
    case SDLK_ESCAPE:
        Window::manager->setCurrentWindowState(WindowState::Type::GAME);
        break;
    default:
        break;
    }
}

void Event::handleGameEvents() {
    switch (Game::player->state) {
    case Player::State::FREE:
        handleFreeState();
        break;
    case Player::State::IN_DIALOG:
        handleDialogState();
        break;
    default:
        break;
    }
}

void Event::handlePauseMenuEvents() {
    if (e.type != SDL_KEYUP)
        return;

    const SDL_KeyCode k = SDL_KeyCode(e.key.keysym.sym);
    if (KeyMap::Key[k] == Event::ID::PAUSE) {
        window->resumeGame();
        return;
    }

    switch (k) {
    case SDLK_q:
        if (SDL_GetModState() & KMOD_CTRL)
            window->quitGame();
        break;
    case SDLK_r:
        if (SDL_GetModState() & KMOD_CTRL)
            window->resumeGame();
        break;
    case SDLK_s:
        Save::Update(Game::WorldID);
        break;
    default:
        break;
    }
}

void Event::handlePowerMenuEvents() {
    if (e.type != SDL_KEYUP) return;

    const SDL_KeyCode k = SDL_KeyCode(e.key.keysym.sym);
    if (KeyMap::Key[k] == Event::ID::OPEN_POWER_MENU)
        window->resumeGame();
}

void Event::handleInventoryMenuEvents() {
    if (e.type != SDL_KEYUP) return;

    const SDL_KeyCode k = SDL_KeyCode(e.key.keysym.sym);
    if (KeyMap::Key[k] == Event::ID::OPEN_INVENTORY)
        window->resumeGame();
}

void Event::handleQuestMenuEvents() {
    if (e.type != SDL_KEYUP) return;

    const SDL_KeyCode k = SDL_KeyCode(e.key.keysym.sym);
    if (KeyMap::Key[k] == Event::ID::OPEN_QUEST_MENU)
        window->resumeGame();
}

void Event::handleDeathMenuEvents() {
    if (e.type != SDL_KEYUP)
        return;

    switch (e.key.keysym.sym) {
    case SDLK_q:
        if (SDL_GetModState() & KMOD_CTRL)
            window->quitGame();
        break;
    case SDLK_r:
        if (SDL_GetModState() & KMOD_CTRL)
            window->loadLastGameSave();
        break;
    default:
        break;
    }
}

void Event::handleIdentityMenuEvents() {
    if (e.type != SDL_KEYUP) return;

    const SDL_KeyCode k = SDL_KeyCode(e.key.keysym.sym);
    if (KeyMap::Key[k] == Event::ID::OPEN_IDENTITY_MENU)
        window->resumeGame();
}

void Event::handleFreeState() {
    SDL_KeyCode k = SDL_KeyCode(e.key.keysym.sym);

    if (e.type == SDL_KEYDOWN) {
        switch (KeyMap::Key[k]) {
        case Event::ID::MOVE_UP:
            Tutorial::Complete(Tutorial::Step::MOVEMENTS);
            Game::player->playAnimation("Walk");
            Game::player->velocity.y = -1;
            break;
        case Event::ID::MOVE_DOWN:
            Tutorial::Complete(Tutorial::Step::MOVEMENTS);
            Game::player->playAnimation("Walk");
            Game::player->velocity.y = 1;
            break;
        case Event::ID::MOVE_LEFT:
            Tutorial::Complete(Tutorial::Step::MOVEMENTS);
            Game::player->playAnimation("Walk");
            Game::player->velocity.x = -1;
            Game::player->setFlip(SDL_FLIP_HORIZONTAL);
            break;
        case Event::ID::MOVE_RIGHT:
            Tutorial::Complete(Tutorial::Step::MOVEMENTS);
            Game::player->playAnimation("Walk");
            Game::player->velocity.x = 1;
            Game::player->setFlip(SDL_FLIP_NONE);
            break;
        case Event::ID::INTERACT:
            Game::player->interaction = Interaction::USE;
            break;
        case Event::ID::BODY_CONTROL:
            Tutorial::Complete(Tutorial::Step::USE_CONTROL_POWER);
            if (Game::player->controlled)
                Game::player->releaseControledEntity();
            else
                Game::player->interaction = Interaction::TAKE_CONTROL;
            break;
        case Event::ID::BODY_RESURRECTION:
            if (Game::player->haveUnlockedPower(Power::BODY_RESURRECTION))
                Game::player->interaction = Interaction::RESURRECT;
            break;
        case Event::ID::UNKNOWN:
        default:
            break;
        }
    }

    if (e.type == SDL_KEYUP) {
        switch (KeyMap::Key[k]) {
        case Event::ID::MOVE_UP:
        case Event::ID::MOVE_DOWN:
            Game::player->playAnimation("Idle");
            Game::player->velocity.y = 0;
            break;
        case Event::ID::MOVE_LEFT:
        case Event::ID::MOVE_RIGHT:
            Game::player->playAnimation("Idle");
            Game::player->velocity.x = 0;
            break;
        case Event::ID::INTERACT:
        case Event::ID::BODY_CONTROL:
        case Event::ID::BODY_RESURRECTION:
            Game::player->interaction = Interaction::NONE;
            break;
        case Event::ID::UNKNOWN:
        default:
            raise(KeyMap::Key[k]);
            break;
        }
    }
}

void Event::handleDialogState() {
    if (e.type != SDL_KEYUP)
        return;

    SDL_KeyCode k = SDL_KeyCode(e.key.keysym.sym);

    switch (KeyMap::Key[k]) {
    case Event::ID::PAUSE:
        window->pauseGame();
        break;
    case Event::ID::VALID_DIALOG:
        Game::player->interactingWith->validateDialog();
        break;
    case Event::ID::NEXT_ANSWER:
        Game::player->interactingWith->updateDialogSelectedAnswer(1);
        break;
    case Event::ID::PREVIOUS_ANSWER:
        Game::player->interactingWith->updateDialogSelectedAnswer(-1);
        break;
    case Event::ID::UNKNOWN:
    default:
        break;
    }
}
