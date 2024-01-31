#include "include/Save.h"

#include "include/Game/Game.h"

#include <fstream>

bool Save::Auto = false;
std::string Save::pathToSaveFolder = "./data/worlds/";

bool Save::Exist(int sid) {
    fs::path path(pathToSaveFolder + std::to_string(sid));

    return fs::exists(path);
}

bool Save::Create(int sid) {
    if (Save::Exist(sid))
        return false;

    fs::path path(pathToSaveFolder + std::to_string(sid));

    fs::create_directory(path);

    CreatePlayer(path / "player.json");

    CreateIsland_0(path / "island-0.json");
    CreateIsland_1(path / "island-1.json");

    // save world name
    std::ifstream infile("./config.json");
    json config;
    infile >> config;
    infile.close();

    config["world " + std::to_string(sid) + " name"] = Game::WorldName;

    std::ofstream outfile("./config.json");
    outfile << std::setw(2) << config << std::endl;
    outfile.close();

    return true;
}

bool Save::Erase(int sid) {
    if (!Save::Exist(sid))
        return false;

    fs::path path(pathToSaveFolder + std::to_string(sid));

    fs::remove_all(path);

    // reset world name and time
    std::ifstream infile("./config.json");
    json config;
    infile >> config;
    infile.close();

    config["world " + std::to_string(sid) + " name"] = "World " + std::to_string(sid);
    config["world " + std::to_string(sid) + " time"] = "00:00:00";

    std::ofstream outfile("./config.json");
    outfile << std::setw(2) << config << std::endl;
    outfile.close();

    return true;
}

bool Save::Update(int sid) {
    if (!Save::Exist(sid))
        return false;

    fs::path path(pathToSaveFolder + std::to_string(sid));

    // SAVE ISLANDS

    std::map<std::string, Island *> islands = Game::GetExploredIslands();

    for (auto island : islands)
        SaveIsland(island.second, path / (island.first + ".json"));

    // SAVE PLAYERS

    SavePlayer(path / "player.json");

    return true;
}

PlayerStructure Save::LoadPlayer(int sid) {
    PlayerStructure p;

    std::ifstream infile(pathToSaveFolder + std::to_string(sid) + "/player.json");
    json player;
    infile >> player;
    infile.close();

    p.name = player["name"];
    p.hp = player["hp"];

    p.numen_level = player["mental power"];
    p.power[Power::BODY_RESURRECTION] = player["res power unlocked"];
    p.power[Power::BODY_EXPLOSION] = player["exp power unlocked"];
    p.power[Power::SHIELD] = player["shield power unlocked"];

    p.island = player["island"];
    p.pos.x = player["x"];
    p.pos.y = player["y"];

    p.state = player["state"];

    auto entity = player["controlled entity"];
    p.controlled_entity.type = entity["type"];
    p.controlled_entity.name = entity["name"];

    if (p.controlled_entity.type == Entity::Type::UNKNOWN)
        return p;

    switch (p.controlled_entity.type)
    {
    case Entity::Type::PLAYER:
        break;
    case Entity::DOLL:
        p.controlled_entity.pos.x = entity["x"];
        p.controlled_entity.pos.y = entity["y"];
        p.controlled_entity.inv = LoadInventory(entity["inventory"]);
        break;
    case Entity::Type::NON_PLAYER_CHARACTER:
    default:
        p.controlled_entity.species = entity["species"];
        p.controlled_entity.behavior = entity["behavior"];
        p.controlled_entity.hp = entity["hp"];
        p.controlled_entity.npc_hasdialog = entity["dialog"];
        p.controlled_entity.pos.x = entity["x"];
        p.controlled_entity.pos.y = entity["y"];
        p.controlled_entity.inv = LoadInventory(entity["inventory"]);
        break;
    }

    return p;
}

json Save::LoadIsland(int sid, std::string name) {
    std::ifstream infile(pathToSaveFolder + std::to_string(sid) + "/" + name + ".json");
    json island;
    infile >> island;
    infile.close();
    return island;
}

Inventory Save::LoadInventory(json inventory) {
    Inventory inv;

    inv.capacity = inventory["capacity"];

    for (auto i : inventory["items"])
    {
        inv.item.push_back(Item::Create(i));
    }

    return inv;
}

void Save::CreatePlayer(fs::path path) {
    json player = {
        {"name", "unknown"},
        {"hp", Entity::MAX_HP},

        {"mental power", 1}, // start with 1 mental power
        {"res power unlocked", false},
        {"exp power unlocked", false},
        {"shield power unlocked", false},

        {"island", "island-0"},
        {"x", 384},
        {"y", 768},

        {"state", Player::State::FREE},

        {"controlled entity", {{"type", Entity::Type::UNKNOWN}, {"name", "noone"}, {"inventory", {{"capacity", 0}, {"items", json::array()}}}}}};

    std::ofstream outfile(path);
    outfile << std::setw(2) << player << std::endl;
    outfile.close();
}

void Save::CreateIsland_0(fs::path path) {
    json island = {
        {"name", "island-0"},
        {"width", 15},
        {"height", 11},
        {"tiles", {{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}, {9, 9, 9, 9, 4, 3, 3, 3, 3, 3, 3, 5, 9, 9, 9}, {9, 9, 4, 3, 13, 0, 0, 0, 0, 0, 0, 12, 3, 5, 9}, {9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9}, {9, 4, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9}, {9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9}, {9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9}, {9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9}, {9, 1, 0, 0, 0, 0, 0, 10, 6, 6, 6, 6, 6, 8, 9}, {9, 7, 6, 6, 6, 6, 6, 8, 9, 9, 9, 9, 9, 9, 9}, {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}}},
        {"portals", {{{"x", 1280}, {"y", 512}, {"destination", "island-1"}, {"destinationX", 768}, {"destinationY", 896}, {"opened", false}}}},
        {"entities", {
            {
                {"type", Entity::Type::DOLL}, 
                {"x", 768}, 
                {"y", 384}, 
                {"inventory", {
                    {"capacity", 1}, 
                    {"items", {Item::ID::LAPIS_VITAE}}
                }}
            }, 
            {
                {"type", Entity::Type::DEAD_BODY},
                {"owner type", Entity::Type::NON_PLAYER_CHARACTER},
                {"species", Entity::Species::GOBLIN},
                {"behavior", NPC::Behavior::STATIC},
                {"name", "UNKNOWN"},
                {"x", 1024},
                {"y", 384},
                {"dialog", false}
            }
        }},
        {"items", {{{"x", 1024}, {"y", 512}, {"id", Item::ID::LAPIS_VITAE}}}}};

    std::ofstream outfile(path);
    outfile << std::setw(2) << island << std::endl;
    outfile.close();
}

void Save::CreateIsland_1(fs::path path) {
    json island = {
        {"name", "island-1"},
        {"width", 30},
        {"height", 20},
        {"tiles", {{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5}, {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4, 3, 13, 0, 0, 0, 0, 0, 0, 0, 0, 18, 17, 17, 17, 17, 19, 0, 0, 2}, {9, 9, 9, 9, 9, 9, 9, 4, 3, 3, 13, 0, 0, 0, 0, 0, 0, 0, 0, 18, 17, 26, 14, 14, 14, 14, 25, 19, 0, 2}, {9, 9, 9, 9, 9, 4, 3, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 14, 14, 14, 14, 14, 14, 14, 16, 0, 2}, {9, 9, 4, 3, 3, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 17, 26, 14, 14, 14, 14, 14, 14, 14, 25, 19, 2}, {9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 16, 2}, {9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 16, 2}, {9, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 24, 14, 14, 14, 14, 14, 14, 14, 14, 14, 16, 2}, {9, 4, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 14, 14, 14, 14, 14, 14, 14, 14, 14, 16, 2}, {9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 20, 24, 14, 14, 14, 14, 14, 14, 14, 16, 2}, {9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 20, 24, 14, 14, 14, 23, 20, 22, 2}, {4, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 20, 20, 20, 22, 0, 0, 2}, {1, 0, 0, 0, 0, 18, 17, 17, 17, 17, 19, 0, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, {1, 0, 0, 18, 17, 26, 14, 14, 14, 14, 16, 0, 2, 7, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}, {1, 0, 0, 15, 14, 14, 14, 14, 14, 14, 16, 0, 12, 5, 7, 6, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 8}, {1, 0, 0, 15, 14, 14, 14, 14, 14, 23, 22, 0, 0, 12, 3, 3, 13, 0, 0, 0, 0, 0, 0, 0, 0, 10, 6, 6, 8, 9}, {1, 0, 0, 21, 24, 14, 14, 14, 23, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 6, 8, 9, 9, 9, 9}, {1, 0, 0, 0, 21, 20, 20, 20, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 6, 8, 9, 9, 9, 9, 9, 9}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 6, 6, 8, 9, 9, 9, 9, 9, 9, 9, 9}, {7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}}},
        {"portals", {{{"x", 768}, {"y", 896}, {"destination", "island-0"}, {"destinationX", 1280}, {"destinationY", 512}, {"opened", false}}}},
        {"entities", {
            {
                {"type", Entity::Type::NON_PLAYER_CHARACTER}, 
                {"species", Entity::Species::HUMAN},
                {"behavior", NPC::Behavior::STATIC}, 
                {"name", "Guide"}, 
                {"hp", Entity::MAX_HP}, 
                {"x", 1024}, 
                {"y", 512}, 
                {"dialog", true}, 
                {"inventory", {
                    {"capacity", 0}, 
                    {"items", json::array()}
                }}
            },
            {
                {"type", Entity::Type::NON_PLAYER_CHARACTER},
                {"species", Entity::Species::GOBLIN},
                {"behavior", NPC::Behavior::RANDOM_MOVEMENT},
                {"name", "Traveler"},
                {"hp", Entity::MAX_HP},
                {"x", 1280},
                {"y", 768},
                {"dialog", false},
                {"inventory", {
                    {"capacity", 1}, 
                    {"items", json::array()}
                }}
            }
        }},
        {"items", json::array()}
    };

    std::ofstream outfile(path);
    outfile << std::setw(2) << island << std::endl;
    outfile.close();
}

void Save::SavePlayer(fs::path path) {
    std::ifstream infile(path);
    json data;
    infile >> data;
    infile.close();

    PlayerStructure player = Game::player->getStructure();

    data["name"] = player.name;
    data["hp"] = player.hp;

    data["mental power"] = player.numen_level;
    data["res power unlocked"] = player.power[Power::BODY_RESURRECTION];
    data["exp power unlocked"] = player.power[Power::BODY_EXPLOSION];
    data["shield power unlocked"] = player.power[Power::SHIELD];

    data["island"] = player.island;
    data["x"] = player.pos.x;
    data["y"] = player.pos.y;

    data["state"] = player.state;

    switch (player.controlled_entity.type)
    {
    case Entity::Type::PLAYER:
        break;
    case Entity::Type::NON_PLAYER_CHARACTER:
    default:
        data["controlled entity"] = OrganizeNPC(player.controlled_entity);
        break;
    }

    std::ofstream outfile(path);
    outfile << std::setw(2) << data << std::endl;
    outfile.close();
}

void Save::SaveIsland(Island *island, fs::path path) {
    std::ifstream infile(path);
    json data;
    infile >> data;
    infile.close();

    std::vector<PortalStructure> pdata = island->getPortals();
    std::vector<json> portals;
    for (PortalStructure pd : pdata)
    {
        json p = {
            {"x", pd.pos.x},
            {"y", pd.pos.y},
            {"destination", pd.dest},
            {"destinationX", pd.dest_pos.x},
            {"destinationY", pd.dest_pos.y},
            {"opened", pd.opened}};
        portals.push_back(p);
    }
    data["portals"] = portals;

    std::vector<EntityStructure> edata = island->getEntities();
    std::vector<json> entities;
    for (EntityStructure ed : edata)
    {
        json e;
        switch (ed.type)
        {
        case Entity::Type::NON_PLAYER_CHARACTER:
            e = OrganizeNPC(ed);
            break;
        case Entity::Type::DOLL:
            e = OrganizeDoll(ed);
            break;
        case Entity::Type::DEAD_BODY:
            e = OrganizeDeadBody(ed);
            break;
        default:
            break;
        }
        entities.push_back(e);
    }
    data["entities"] = entities;

    std::vector<std::pair<Vector2D, Item::ID>> idata = island->getItems();
    std::vector<json> items;
    for (std::pair<Vector2D, Item::ID> i : idata) 
        items.push_back(OrganizeItem(i));
    data["items"] = items;

    std::ofstream outfile(path);
    outfile << std::setw(2) << data << std::endl;
    outfile.close();
}

json Save::OrganizeInventory(Inventory inventory) {
    std::vector<Item::ID> items;

    for (Item *i : inventory.item)
        items.push_back(i->id);

    json inv = {
        {"capacity", inventory.capacity},
        {"items", items}};

    return inv;
}

json Save::OrganizeItem(std::pair<Vector2D, int> i) {
    json item = {
        {"x", i.first.x},
        {"y", i.first.y},
        {"id", i.second}
    };

    return item;
}

json Save::OrganizeNPC(EntityStructure npcs) {
    json npc = {
        {"type", npcs.type},
        {"species", npcs.species},
        {"behavior", npcs.behavior},
        {"name", npcs.name},
        {"hp", npcs.hp},
        {"x", npcs.pos.x},
        {"y", npcs.pos.y},
        {"dialog", npcs.npc_hasdialog},
        {"inventory", OrganizeInventory(npcs.inv)}};
    return npc;
}

json Save::OrganizeDoll(EntityStructure dolls) {
    json doll = {
        {"type", dolls.type},
        {"x", dolls.pos.x},
        {"y", dolls.pos.y},
        {"inventory", OrganizeInventory(dolls.inv)}};
    return doll;
}

json Save::OrganizeDeadBody(EntityStructure s) {
    json body = {
        {"type", s.type},
        {"owner type", s.type2},
        {"species", s.species},
        {"behavior", s.behavior},
        {"name", s.name},
        {"x", s.pos.x},
        {"y", s.pos.y},
        {"dialog", s.npc_hasdialog}
    };
    return body;
}
