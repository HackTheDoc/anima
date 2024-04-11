#pragma once

#include <map>
#include <SDL2/SDL.h>

#include "Event.h"

/// @brief Represent the map of the keyboard keys and the event that can be generated when pressing them
class KeyMap {
public:
    /// @brief associate a keycode to the event it must generate when pressed
    static std::map<SDL_KeyCode, Event::ID> Key;

    /// @brief set a new keycode to an event id
    /// @param eid id of the evet to update
    /// @param kcode new keycode
    static bool Set(const Event::ID eid, const SDL_KeyCode kcode);

    /// @brief find the keycode associated to an event id
    /// @param eid id to search
    /// @return the approriate keycode
    static SDL_KeyCode GetKeyCode(const Event::ID eid);
};
