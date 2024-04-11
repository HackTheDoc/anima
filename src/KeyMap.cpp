#include "include/KeyMap.h"

#include "include/Save.h"

std::map<SDL_KeyCode, Event::ID> KeyMap::Key = {};

bool KeyMap::Set(Event::ID eid, SDL_KeyCode kcode) {
    std::map<SDL_KeyCode, Event::ID>::iterator it = KeyMap::Key.begin();

    while (it != KeyMap::Key.end() && (it->first != kcode || (it->first == kcode && it->second == eid)))
        it++;

    if (it != KeyMap::Key.end())
        return false;

    Key[kcode] = eid;

    Save::SaveConfig();

    return true;
}

SDL_KeyCode KeyMap::GetKeyCode(Event::ID eid) {
    std::map<SDL_KeyCode, Event::ID>::iterator it = KeyMap::Key.begin();

    while (it != KeyMap::Key.end() && it->second != eid)
        it++;

    return it->first;
}
