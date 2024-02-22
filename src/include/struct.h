#pragma once

#include <map>
#include <array>
#include <string>
#include <vector>
#include <variant>
#include <SDL2/SDL.h>

#include "Game/Game.h"

using ItemID = Item::ID;
using PlayerState = Player::State;
using EntityType = Entity::Type;
using EntitySpecies = Entity::Species;
using EntityBehavior = Entity::Behavior;

namespace Struct {
    struct Config {
        bool autosave;
        bool tutorial;
        Uint8 language;
        Uint32 window_mode;
        std::map<std::string, SDL_KeyCode> controls;
    };

    struct Teleporter {
        Vector2D pos;
        std::string dest;
        Vector2D dest_pos;
        int damage_level;
        bool is_door{false};
    };

    struct Map {
        int width;
        int height;
        std::vector<std::vector<Tile::Type>> tiles;
    };

    struct Item {
        Vector2D pos;
        ItemID id;
    };

    struct Inventory {
        size_t capacity;
        std::vector<Item> items;
    };

    struct NPC {
        EntitySpecies species;
        EntityBehavior behavior;
        std::string name;
        int hp;
        Vector2D pos;
        bool hasdialog;
        Inventory inventory;
    };

    struct Doll {
        Vector2D pos;
        Inventory inventory;
    };

    struct DeadBody {
        EntitySpecies species;
        Vector2D pos;
        Inventory inventory;
        EntityType o_type;
        EntityBehavior o_behavior;
        std::string o_name;
        bool o_hasdialog;
    };

    struct Entity {
        std::variant<
            NPC,
            Doll,
            DeadBody
        > e;

        ~Entity() {
            e.~variant();
        }
    };

    struct Island {
        std::string name;
        Map map;
        std::vector<Teleporter> portals;
        std::vector<Item> items;
        std::vector<Entity> entities;
    };

    struct Player {
        std::string name;
        int hp;
        int numen_level;
        std::array<bool, 3> power;

        PlayerState state;

        int tutorial_step;

        Quest::ID curr_main_quest;
        std::vector<Quest::ID> curr_other_quests;

        std::string curr_island_on;
        Vector2D pos;

        bool is_controlling_an_entity;
        Entity controlled_entity;
    };

    struct Game {
        int world_id;
        Statistics stats;
        Player player;
        std::map<std::string, Island> islands;
    };

}; // namespace Struct
