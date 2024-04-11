#pragma once

#include <string>
#include <SDL2/SDL.h>

class Window;

class Event {
private:
    /// @brief owner window
    Window* window;

public:
    enum ID {
        UNKNOWN,

        SET_LANGUAGE_TO_ENGLISH,
        SET_LANGUAGE_TO_FRENCH,
        SET_WINDOW_TO_FULLSCREEN,
        SET_WINDOW_TO_DEFAULT,

        // BUTTONS 

        QUIT,
        OPEN_MAIN_MENU,

        OPEN_OPTIONS,
        OPEN_GENERAL_SETTINGS,
        OPEN_CONTROLS_SETTINGS,

        OPEN_CREDITS,

        OPEN_PLAY_MENU,
        LOAD_SAVE,
        ERASE_SAVE,
        SELECT_SAVE_1,
        SELECT_SAVE_2,
        SELECT_SAVE_3,
        SELECT_SAVE_4,
        VALID_WORLD_NAME_INPUT,
        QUIT_INPUT_FIELD,

        QUIT_GAME,

        SAVE_GAME,
        LOAD_LAST_SAVE,

        RESUME_GAME,
        PAUSE,
        OPEN_INVENTORY,
        OPEN_POWER_MENU,
        OPEN_QUEST_MENU,
        OPEN_IDENTITY_MENU,
        OPEN_PLAYER_DEATH_MENU,

        // GAME RELATED

        //      FREE

        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,

        INTERACT,
        BODY_CONTROL,
        BODY_RESURRECTION,

        //      DIALOG

        VALID_DIALOG,
        NEXT_ANSWER,
        PREVIOUS_ANSWER
    };

    /// @brief classic SDL_Event object
    SDL_Event e;

    Event();
    ~Event();

    /// @brief set the owner window pointer
    /// @param w
    void linkTo(Window* w);

    /// @brief handle user's keyboard inputs
    void handleKeyboardInputs();

    /// @brief check for a mouse left click
    /// @return
    bool mouseClickLeft();

    /// @brief check for a mouse right click
    /// @return
    bool mouseClickRight();

    /// @brief check wether a specific event been raised or not
    /// @param id
    /// @return
    bool raised(const Event::ID id);

    /// @brief raise a specific event
    /// @param id 
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
