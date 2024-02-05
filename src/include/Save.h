#pragma once

#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

using json = nlohmann::json;

class Player;
class Island;
struct EntityStructure;
struct PlayerStructure;
struct Inventory;
class Vector2D;

class Save {
public:
    /// @brief autosave mode
    static bool Auto;

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

    /// @brief load the player's informations depending on the considerate save
    /// @param sid id of the save to load from
    /// @return data structure of the player
    static PlayerStructure LoadPlayer(int sid);

    /// @brief load an island based on it's name and the id of the save
    /// @param sid id of the save to load from
    /// @param name name of the island to load
    /// @return json obect containing the island's data
    static json LoadIsland(int sid, std::string name);

    /// @brief load an inventory from the json structure
    /// @param inventory 
    /// @return the structured inventory or an error if the entry json structure isn't appropriate
    static Inventory LoadInventory(json inventory);
private:
    /// @brief path to the folder where the save are stored
    static std::string pathToSaveFolder;

    /* ----- CREATE ----- */
    
    /// @brief create a new player.json file at the given path
    /// @param path be careful of the extension
    static void CreatePlayer(fs::path path);

    /// @brief create a new island-0.json file a the given path
    /// @param path be careful of the extension
    static void CreateIsland_0(fs::path path);

    /// @brief create a new island-1.json file a the given path
    /// @param path be careful of the extension
    static void CreateIsland_1(fs::path path);
    
    /* ----- SAVE ----- */

    /// @brief save the player state in a file a the given path
    /// @param path be careful of the extension
    static void SavePlayer(fs::path path);

    /// @brief save an island informations (entities, portals, etc)
    /// @param island pointer to the island to save
    /// @param path path to the island file (careful with the extension)
    static void SaveIsland(Island* island, fs::path path);

    /* ----- STRUCTURE CREATION ----- */

    static json CreateInventory(const int capacity, std::vector<int> items = {});
    
    static json CreateItem(const int x, const int y, const int id);

    /// @brief Create a portal's json structure
    /// @param xp x position on the map (in pixels)
    /// @param yp y position on the map (in pixels)
    /// @param dest name of the destination island
    /// @param xd x position on the destination map (in pixels)
    /// @param yd y position on the destination map (in pixels)
    /// @param opened (default: false)
    /// @return 
    static json CreatePortal(const int xp, const int yp, const std::string& dest, const int xd, const int yd, const int damage_level);

    static json CreateNoone();
    
    static json CreateNPC(const int x, const int y, const int species, const int behavior, const std::string& name, const json& inventory, const int hp=3, const bool hasdialog=false);

    static json CreateDoll(const int x, const int y, const json& inv);

    static json CreateDeadBody(const int x, const int y, const int species, const int otype, const int obehavior, const std::string& oname, const json& oinv, const bool ohasdialog=false);

    /* ----- STRUCTURE ORGANIZATION ----- */
    /// @brief structure a json object with an inventory's informations
    /// @param inventory inventory structure
    /// @return structured json object
    static json OrganizeInventory(Inventory inventory);

    static json OrganizeItem(std::pair<Vector2D, int> i);

    /// @brief structure a json object with a NPC's informations
    /// @param npcs data structure of the NPC
    /// @return structured json object
    static json OrganizeNPC(EntityStructure npcs);

    /// @brief structure a json object with a DOLL's informations
    /// @param npcs data structure of the DOLL
    /// @return structured json object
    static json OrganizeDoll(EntityStructure dolls);    

    /// @brief structure a json object with a DeadBody's informations
    /// @param npcs data structure of the DeadBody
    /// @return structured json object
    static json OrganizeDeadBody(EntityStructure s); 
};
