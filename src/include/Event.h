#pragma once

#include <SDL2/SDL.h>

#include "UI/UIButtons.h"
#include "UI/UIChoice.h"

class Window;

class Event {
private:
    /// @brief owner window
    Window *window;

public:
    enum ID {
        UNKNOWN,

        PAUSE,
        OPEN_POWER_MENU,
        OPEN_INVENTORY,
        OPEN_QUEST_MENU,
        OPEN_PLAYER_DEATH_MENU,
        OPEN_IDENTITY_MENU,

        // FREE
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,

        INTERACT,
        BODY_CONTROL,
        BODY_RESURRECTION,

        // DIALOG
        VALID_DIALOG,
        NEXT_ANSWER,
        PREVIOUS_ANSWER
    };

    /// @brief classic SDL_Event object
    SDL_Event e;

    Event();
    ~Event();

    /// @brief set the owner window pointer
    /// @param w pointer to the new owner
    void linkTo(Window *w);

    /// @brief handle a button click
    /// @param id id of the button
    void handleButtonClick(const UIButton::ID id);

    /// @brief handle a selection choice
    /// @param id id of the choice
    void handleSelection(const UIChoice::ID id);

    /// @brief handle user's keyboard inputs
    void handleKeyboardInputs();

    /// @brief check for a mouse left click
    /// @return true when mouse click left else false
    bool mouseClickLeft();

    /// @brief check for a mouse right click
    /// @return true when mouse click right else false
    bool mouseClickRight();

    /// @brief check wether a specific event been raised or not
    /// @param id
    /// @return
    bool raised(const Event::ID id);

    void raise(const Event::ID id);

private:
    /// TODO: decide wether i will keep those shortcuts or not...

    void handleMainMenuEvents();
    void handleOptionsMenuEvents();
    void handleCreditsEvents();

    void handleCinematicEvents();

    void handleGameEvents();
    void handlePauseMenuEvents();
    void handlePowerMenuEvents();
    void handleInventoryMenuEvents();
    void handleQuestMenuEvents();
    void handleDeathMenuEvents();
    void handleIdentityMenuEvents();

    /// @brief handle free state authorized events
    void handleFreeState();

    /// @brief handle dialog state authorized events
    void handleDialogState();
};

std::string to_string(const Event::ID eid);
