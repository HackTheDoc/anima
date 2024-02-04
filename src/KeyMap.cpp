#include "include/KeyMap.h"

#include <fstream>
#include <nlohmann/json.hpp>

std::map<SDL_KeyCode, Event::ID> KeyMap::Key = {};

void KeyMap::Load() {
    std::fstream infile("./config.json");
    nlohmann::json config;
    infile >> config;
    infile.close();

    // raw keymap
    auto rkmap = config["controls"];

    KeyMap::Key = {
        {rkmap["pause"]             , Event::ID::PAUSE              },
        {rkmap["power menu"]        , Event::ID::OPEN_POWER_MENU    },
        {rkmap["inventory"]         , Event::ID::OPEN_INVENTORY     },
        {rkmap["quest menu"]        , Event::ID::OPEN_QUEST_MENU    },

        {rkmap["move up"]           , Event::ID::MOVE_UP            },
        {rkmap["move down"]         , Event::ID::MOVE_DOWN          },
        {rkmap["move left"]         , Event::ID::MOVE_LEFT          },
        {rkmap["move right"]        , Event::ID::MOVE_RIGHT},

        {rkmap["interact"]          , Event::ID::INTERACT           },
        {rkmap["take control"]      , Event::ID::BODY_CONTROL       },
        {rkmap["body resurrection"] , Event::ID::BODY_RESURRECTION  },

        {rkmap["valid dialog"]      , Event::ID::VALID_DIALOG       },
        {rkmap["next answer"]       , Event::ID::NEXT_ANSWER        },
        {rkmap["previous answer"]   , Event::ID::PREVIOUS_ANSWER    },
    };
}

void KeyMap::Save() {
    std::fstream infile("./config.json");
    nlohmann::json config;
    infile >> config;
    infile.close();

    // save default keymap
    for (std::map<SDL_KeyCode, Event::ID>::iterator it = KeyMap::Key.begin(); it != KeyMap::Key.end(); it++)
    {
        SDL_KeyCode kcode = it->first;
        Event::ID eid = it->second;
        std::string ename = KeyMap::EventName(eid);

        config["controls"][ename] = kcode;
    }

    std::ofstream outfile("./config.json");
    outfile << std::setw(2) << config << std::endl;
    outfile.close();
}

bool KeyMap::Set(Event::ID eid, SDL_KeyCode kcode) {
    std::map<SDL_KeyCode, Event::ID>::iterator it = KeyMap::Key.begin();

    while (it != KeyMap::Key.end() && (it->first != kcode || (it->first == kcode && it->second == eid)))
        it++;

    if (it != KeyMap::Key.end())
        return false;

    std::fstream infile("./config.json");
    nlohmann::json config;
    infile >> config;
    infile.close();

    std::string ename = EventName(eid);
    config["controls"][ename] = kcode;

    std::ofstream outfile("./config.json");
    outfile << std::setw(2) << config << std::endl;
    outfile.close();

    KeyMap::Load();

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
