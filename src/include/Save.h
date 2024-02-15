#pragma once

#include <filesystem>

namespace fs = std::filesystem;

#include "struct.h"

class Player;
class Island;
struct EntityStructure;
struct PlayerStructure;
struct Inventory;
class Vector2D;

class Save {
public:
    /* ----- CONFIG ----- */
    static void SaveConfig();
    static Struct::Config LoadConfig();

    /* ----- KEYMAP ----- */
    static void Key(const std::string& ename, const SDL_KeyCode kcode);

    /* ----- GAME ----- */

    /// @brief autosave mode
    static bool Auto;

    static void PlayTime(const int wid);

    static std::pair<std::string, std::string> GetWorldInfo(const int wid);

    /// @brief check the existance of a save
    /// @param sid id of the save
    /// @return true if the save exist else false
    static bool Exist(int sid);

    /// @brief create a new save
    /// @param sid id of the save
    /// @return true if the save has been created else false
    static bool Create(int sid);

    /// @brief erase an existing save
    /// @param sid id of the save
    /// @return true if the save has been erased else false
    static bool Erase(int sid);

    /// @brief update a save files
    /// @param sid id of the save
    /// @return true if the save has been updated else false
    static bool Update(int sid);

    /* ----- LOAD ----- */

    static Struct::Game Load(int sid);

    static Struct::Player LoadPlayer();

    static Struct::Island LoadIsland(const std::string& island_name);

private:
    /// @brief path to the folder where the save are stored
    static std::string pathToSaveFolder;

    /* ----- CONFIG ----- */
    static void CreateConfig();

    /* ----- GAME ----- */

        /* ----- CREATE ----- */

    static Struct::Portal CreatePortal(const int x, const int y, const std::string& dest, const int dx, const int dy, const int dmg_lvl);

    static Struct::Map CreateMap(const int width, const int height, const std::vector<std::vector<int>>& rmap);

    static Struct::Item CreateItem(const int x, const int y, const Item::ID id);

    static Struct::Inventory CreateInventory(const size_t capacity, std::vector<Item::ID> items = {});

    static Struct::Entity CreateNPC(const int x, const int y, const EntitySpecies species, const EntityBehavior behavior, const std::string& name, const Struct::Inventory& inv, const int hp, const bool hasdialog=false);

    static Struct::Entity CreateDoll(const int x, const int y, const Struct::Inventory& inv);
    
    static Struct::Entity CreateDeadBody(const int x, const int y, const EntitySpecies species, const EntityType otype, const EntityBehavior obehavior, const std::string& oname, const Struct::Inventory& inv, bool ohasdialog=false);

    static Struct::Player CreatePlayer(const Vector2D& pos);

    // test island
    static Struct::Island CreateIsland_0();

    // another test island
    static Struct::Island CreateIsland_1();

    static Struct::Island CreateIsland_LostTemple(const Vector2D& dpos1, const Vector2D& dpos2, const Vector2D& dpos3);
};
