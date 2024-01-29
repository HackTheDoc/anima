#include "include/Event.h"

#include "include/Game/Game.h"

#include "include/Window.h"

#include "include/WindowState/PlayMenu.h"

#include "include/Save.h"
#include "include/KeyMap.h"

#include <iostream>

std::string to_string(Event::ID eid)
{
    switch (KeyMap::GetKeyCode(eid))
    {
    case SDLK_a:
        return "A";
        break;
    case SDLK_b:
        return "B";
        break;
    case SDLK_c:
        return "C";
        break;
    case SDLK_d:
        return "D";
        break;
    case SDLK_e:
        return "E";
        break;
    case SDLK_f:
        return "F";
        break;
    case SDLK_g:
        return "G";
        break;
    case SDLK_h:
        return "H";
        break;
    case SDLK_i:
        return "I";
        break;
    case SDLK_j:
        return "J";
        break;
    case SDLK_k:
        return "K";
        break;
    case SDLK_l:
        return "L";
        break;
    case SDLK_m:
        return "M";
        break;
    case SDLK_n:
        return "N";
        break;
    case SDLK_o:
        return "O";
        break;
    case SDLK_p:
        return "P";
        break;
    case SDLK_q:
        return "Q";
        break;
    case SDLK_r:
        return "R";
        break;
    case SDLK_s:
        return "S";
        break;
    case SDLK_t:
        return "T";
        break;
    case SDLK_u:
        return "U";
        break;
    case SDLK_v:
        return "V";
        break;
    case SDLK_w:
        return "W";
        break;
    case SDLK_x:
        return "X";
        break;
    case SDLK_y:
        return "Y";
        break;
    case SDLK_z:
        return "Z";
        break;

    case SDLK_UP:
        return Text::Get("UP");
        break;
    case SDLK_DOWN:
        return Text::Get("DOWN");
        break;
    case SDLK_LEFT:
        return Text::Get("LEFT");
        break;
    case SDLK_RIGHT:
        return Text::Get("RIGHT");
        break;

    case SDLK_RALT:
    case SDLK_LALT:
        return "ALT";
        break;
    case SDLK_ESCAPE:
        return "ESC";
        break;
    case SDLK_RETURN:
        return Text::Get("ENTER");
        break;
    case SDLK_RCTRL:
        return "RCTRL";
        break;
    case SDLK_LCTRL:
        return "LCTRL";
        break;
    case SDLK_RSHIFT:
        return "RSHIFT";
        break;
    case SDLK_LSHIFT:
        return "LSHIFT";
        break;
    case SDLK_CAPSLOCK:
        return "CAPS";
        break;
    case SDLK_TAB:
        return "TAB";
        break;

    case SDLK_0:
        return "0";
        break;
    case SDLK_1:
        return "1";
        break;
    case SDLK_2:
        return "2";
        break;
    case SDLK_3:
        return "3";
        break;
    case SDLK_4:
        return "4";
        break;
    case SDLK_5:
        return "5";
        break;
    case SDLK_6:
        return "6";
        break;
    case SDLK_7:
        return "7";
        break;
    case SDLK_8:
        return "8";
        break;
    case SDLK_9:
        return "9";
        break;
    default:
        return "";
        break;
    }
}

Event::Event() {}

Event::~Event() {}

void Event::linkTo(Window *w)
{
    window = w;
}

void Event::handleButtonClick(UIButton::ID id)
{
    switch (id)
    {
    /* ----- MAIN MENU BUTTONS ----- */
    case UIButton::ID::QUIT:
        Window::isRunning = false;
        break;
    case UIButton::ID::PLAY:
        window->openPlayMenu();
        break;
    case UIButton::ID::OPTIONS:
        window->openOptionsMenu();
        break;
    case UIButton::ID::CREDITS:
        window->openCredits();
        break;

    /* ----- PLAY MENU BUTTONS ----- */
    case UIButton::ID::SELECT_SAVE_1:
        PlayMenu::Selection = 1;
        break;
    case UIButton::ID::SELECT_SAVE_2:
        PlayMenu::Selection = 2;
        break;
    case UIButton::ID::SELECT_SAVE_3:
        PlayMenu::Selection = 3;
        break;
    case UIButton::ID::SELECT_SAVE_4:
        PlayMenu::Selection = 4;
        break;
    case UIButton::ID::LOAD_SAVE:
        if (PlayMenu::IsSelectionActived())
        {
            if (!Save::Exist(PlayMenu::Selection) && Game::WorldName == "World 0")
                PlayMenu::OpenWorldNameInput();
            else
                window->openGame(PlayMenu::Selection);
        }
        break;
    case UIButton::ID::ERASE_SAVE:
        if (PlayMenu::IsSelectionActived())
            PlayMenu::RemoveInfos(PlayMenu::Selection);
        Save::Erase(PlayMenu::Selection);
        break;
    case UIButton::ID::QUIT_PLAY_MENU:
        window->openMainMenu();
        break;
    case UIButton::QUIT_WORLD_NAME_INPUT:
        PlayMenu::CloseWorldNameInput();
        break;
    case UIButton::ID::VALID_WORLD_NAME_INPUT:
        PlayMenu::ValidWorldName();
        window->openGame(PlayMenu::Selection);
        break;

    /* ----- PAUSE MENU BUTTONS ----- */
    case UIButton::ID::RESUME_GAME:
        window->resumeGame();
        break;
    case UIButton::ID::SAVE_GAME:
        Save::Update(Game::WorldID);
        break;
    case UIButton::ID::QUIT_GAME:
        window->quitGame();
        break;

    /* ----- OPTIONS MENU BUTTONS ----- */
    case UIButton::ID::QUIT_SETTINGS:
        window->openMainMenu();
        break;
    case UIButton::ID::GENERAL_SETTINGS:
        window->openGeneralOptions();
        break;
    case UIButton::ID::CONTROLS_SETTINGS:
        window->openControlsOptions();
        break;

    /* ----- CREDITS BUTTONS ----- */
    case UIButton::ID::QUIT_CREDITS:
        window->openMainMenu();
        break;

    default:
        break;
    }
}

void Event::handleSelection(UIChoice::ID id)
{
    switch (id)
    {
    case UIChoice::LG_ENGLISH:
        Window::SetLanguage(Text::Language::ENGLISH);
        break;
    case UIChoice::LG_FRENCH:
        Window::SetLanguage(Text::Language::FRENCH);
        break;
    default:
        break;
    }
}

void Event::handleKeyboardInputs()
{
    switch (Window::manager->getCurrentStateID())
    {
    case WindowState::Type::MAIN:
        handleMainMenuEvents();
        break;
    case WindowState::Type::OPTIONS_MENU:
        handleOptionsMenuEvents();
        break;
    case WindowState::Type::CREDITS:
        handleCreditsEvents();
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
    case WindowState::Type::UNKNOWN:
    default:
        break;
    }
}

bool Event::mouseClickLeft()
{
    return e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT;
}

bool Event::mouseClickRight()
{
    return e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT;
}

void Event::handleMainMenuEvents()
{
    if (e.type != SDL_KEYUP || !(SDL_GetModState() & KMOD_CTRL))
        return;
    switch (e.key.keysym.sym)
    {
    case SDLK_q:
        Window::isRunning = false;
        break;
    case SDLK_r:
        window->openMainMenu();
        break;
    /// TODO: DEV ONLY
    case SDLK_e:
        Save::Erase(4);
        window->openGame(4);
        Game::player->unlockPower(Power::BODY_RESURRECTION);
        Game::player->unlockPower(Power::BODY_EXPLOSION);
        Game::player->unlockPower(Power::SHIELD);
        Game::player->modifyNumenLevelBy(+10);
        window->quitGame();
        window->openGame(4);
        break;
    case SDLK_p:
        window->openGame(4);
        break;
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

void Event::handleOptionsMenuEvents()
{
    if (e.type != SDL_KEYUP || !(SDL_GetModState() & KMOD_CTRL))
        return;

    switch (e.key.keysym.sym)
    {
    case SDLK_q:
        window->openMainMenu();
        break;
    case SDLK_g:
        window->openGeneralOptions();
        break;
    case SDLK_c:
        window->openControlsOptions();
        break;
    case SDLK_w:
        window->execute("next window mode");
        break;
    case SDLK_l:
        window->execute("next language");
        break;
    default:
        break;
    }
}

void Event::handleCreditsEvents()
{
    if (e.type != SDL_KEYUP || !(SDL_GetModState() & KMOD_CTRL))
        return;

    switch (e.key.keysym.sym)
    {
    case SDLK_q:
        window->openMainMenu();
        break;
    case SDLK_d:
        window->execute("open url discord");
        break;
    case SDLK_t:
        window->execute("open url twitter");
        break;
    case SDLK_g:
        window->execute("open url github");
        break;
    default:
        break;
    }
}

void Event::handleGameEvents()
{
    switch (Game::player->state)
    {
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

void Event::handlePauseMenuEvents()
{
    if (e.type != SDL_KEYUP)
        return;

    SDL_KeyCode k = SDL_KeyCode(e.key.keysym.sym);
    if (KeyMap::Key[k] == Event::ID::PAUSE)
    {
        window->resumeGame();
        return;
    }

    switch (e.key.keysym.sym)
    {
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

void Event::handlePowerMenuEvents()
{
    if (e.type != SDL_KEYUP)
        return;

    SDL_KeyCode k = SDL_KeyCode(e.key.keysym.sym);
    if (KeyMap::Key[k] == Event::ID::OPEN_POWER_MENU)
    {
        window->resumeGame();
        return;
    }
}

void Event::handleInventoryMenuEvents()
{
    if (e.type != SDL_KEYUP)
        return;

    SDL_KeyCode k = SDL_KeyCode(e.key.keysym.sym);
    if (KeyMap::Key[k] == Event::ID::OPEN_INVENTORY)
    {
        window->resumeGame();
        return;
    }
}

void Event::handleFreeState()
{
    SDL_KeyCode k = SDL_KeyCode(e.key.keysym.sym);

    if (e.type == SDL_KEYDOWN)
    {
        switch (KeyMap::Key[k])
        {
        case Event::ID::MOVE_UP:
            Game::player->playAnimation("Walk");
            Game::player->vSpeed = -1;
            break;
        case Event::ID::MOVE_DOWN:
            Game::player->playAnimation("Walk");
            Game::player->vSpeed = 1;
            break;
        case Event::ID::MOVE_LEFT:
            Game::player->playAnimation("Walk");
            Game::player->hSpeed = -1;
            Game::player->setFlip(SDL_FLIP_HORIZONTAL);
            break;
        case Event::ID::MOVE_RIGHT:
            Game::player->playAnimation("Walk");
            Game::player->hSpeed = 1;
            Game::player->setFlip(SDL_FLIP_NONE);
            break;
        case Event::ID::INTERACT:
            Game::player->interaction = Interaction::USE;
            break;
        case Event::ID::BODY_CONTROL:
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

    if (e.type == SDL_KEYUP)
    {
        switch (KeyMap::Key[k])
        {
        case Event::ID::PAUSE:
            window->pauseGame();
            break;
        case Event::ID::OPEN_POWER_MENU:
            window->openPowerMenu();
            break;
        case Event::ID::OPEN_INVENTORY:
            window->openInventory(Game::player->parseInventory());
            break;
        case Event::ID::MOVE_UP:
        case Event::ID::MOVE_DOWN:
            Game::player->playAnimation("Idle");
            Game::player->vSpeed = 0;
            break;
        case Event::ID::MOVE_LEFT:
        case Event::ID::MOVE_RIGHT:
            Game::player->playAnimation("Idle");
            Game::player->hSpeed = 0;
            break;
        case Event::ID::INTERACT:
        case Event::ID::BODY_CONTROL:
        case Event::ID::BODY_RESURRECTION:
            Game::player->interaction = Interaction::NONE;
            break;
        case Event::ID::UNKNOWN:
        default:
            break;
        }
    }
}

void Event::handleDialogState()
{
    if (e.type != SDL_KEYUP)
        return;

    SDL_KeyCode k = SDL_KeyCode(e.key.keysym.sym);

    switch (KeyMap::Key[k])
    {
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
