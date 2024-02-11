#include "include/KeyMap.h"

#include "include/Save.h"

std::map<SDL_KeyCode, Event::ID> KeyMap::Key = {};

void KeyMap::Reload() {
    const ConfigStruct config = Save::LoadConfig();
    Import(config.controls);
};

void KeyMap::Import(const std::map<std::string, SDL_KeyCode>& rkmap) {
    KeyMap::Key = {
        {rkmap.at("pause")             , Event::ID::PAUSE              },
        {rkmap.at("power menu")        , Event::ID::OPEN_POWER_MENU    },
        {rkmap.at("inventory")         , Event::ID::OPEN_INVENTORY     },
        {rkmap.at("quest menu")        , Event::ID::OPEN_QUEST_MENU    },

        {rkmap.at("move up")           , Event::ID::MOVE_UP            },
        {rkmap.at("move down")         , Event::ID::MOVE_DOWN          },
        {rkmap.at("move left")         , Event::ID::MOVE_LEFT          },
        {rkmap.at("move right")        , Event::ID::MOVE_RIGHT},

        {rkmap.at("interact")          , Event::ID::INTERACT           },
        {rkmap.at("take control")      , Event::ID::BODY_CONTROL       },
        {rkmap.at("body resurrection") , Event::ID::BODY_RESURRECTION  },

        {rkmap.at("valid dialog")      , Event::ID::VALID_DIALOG       },
        {rkmap.at("next answer")       , Event::ID::NEXT_ANSWER        },
        {rkmap.at("previous answer")   , Event::ID::PREVIOUS_ANSWER    },
    };
}

std::map<std::string, SDL_KeyCode> KeyMap::Export() {
    std::map<std::string, SDL_KeyCode> r;

    for (std::map<SDL_KeyCode, Event::ID>::iterator it = KeyMap::Key.begin(); it != KeyMap::Key.end(); it++) {
        SDL_KeyCode kcode = it->first;
        Event::ID eid = it->second;
        std::string ename = KeyMap::EventName(eid);

        r[ename] = kcode;
    }

    return r;
}

bool KeyMap::Set(Event::ID eid, SDL_KeyCode kcode) {
    std::map<SDL_KeyCode, Event::ID>::iterator it = KeyMap::Key.begin();

    while (it != KeyMap::Key.end() && (it->first != kcode || (it->first == kcode && it->second == eid)))
        it++;

    if (it != KeyMap::Key.end())
        return false;

    std::string ename = EventName(eid);

    Save::Key(ename, kcode);

    Reload();

    return true;
}

SDL_KeyCode KeyMap::GetKeyCode(Event::ID eid) {
    std::map<SDL_KeyCode, Event::ID>::iterator it = KeyMap::Key.begin();

    while (it != KeyMap::Key.end() && it->second != eid)
        it++;

    return it->first;
}

std::string KeyMap::EventName(Event::ID eid) {
    switch (eid) {
    case Event::ID::PAUSE:
        return "pause";
    case Event::ID::OPEN_POWER_MENU:
        return "power menu";
    case Event::ID::OPEN_INVENTORY:
        return "inventory";
    case Event::ID::OPEN_QUEST_MENU:
        return "quest menu";
    case Event::ID::MOVE_UP:
        return "move up";
    case Event::ID::MOVE_DOWN:
        return "move down";
    case Event::ID::MOVE_LEFT:
        return "move left";
    case Event::ID::MOVE_RIGHT:
        return "move right";
    case Event::ID::INTERACT:
        return "interact";
    case Event::ID::BODY_CONTROL:
        return "take control";
    case Event::ID::BODY_RESURRECTION:
        return "body resurrection";
    case Event::ID::VALID_DIALOG:
        return "valid dialog";
    case Event::ID::NEXT_ANSWER:
        return "next answer";
    case Event::ID::PREVIOUS_ANSWER:
        return "previous answer";
    default:
        return "unknown";
    }
}
