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

    // create player

    std::vector<Vector2D> doll_pos= {
        {2956, 2956}, // bottom right
        {2260, 2956}, // bottom left
        {2956, 2232}, // top right
        {2260, 2232}  // top left
    };
    int i = rand() % 4;
    CreatePlayer(path / "player.json", doll_pos[i]);
    doll_pos.erase(doll_pos.cbegin() + i);

    // create islands
    i = rand() % 3;
    Vector2D dpos1 = doll_pos[i];
    doll_pos.erase(doll_pos.cbegin() + i);

    i = rand() % 2;
    Vector2D dpos2 = doll_pos[i];
    doll_pos.erase(doll_pos.cbegin() + i);
    
    CreateIsland_LostTemple(path/"lost-temple.json", dpos1, dpos2, doll_pos[0]);

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

    // SAVE PLAYER

    SavePlayer(path / "player.json");

    // SAVE ISLANDS

    std::map<std::string, Island*> islands = Game::GetExploredIslands();

    for (auto island : islands)
        SaveIsland(island.second, path / (island.first + ".json"));

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

    p.curr_main_quest = player["main quest"];
    for (std::string q : player["side quests"])
        p.curr_other_quests.push_back(q);

    auto entity = player["controlled entity"];
    p.controlled_entity.type = entity["type"];

    if (p.controlled_entity.type == Entity::Type::UNKNOWN)
        return p;

    switch (p.controlled_entity.type) {
    case Entity::Type::PLAYER:
        break;
    case Entity::DOLL:
        p.controlled_entity.pos.x = entity["x"];
        p.controlled_entity.pos.y = entity["y"];
        p.controlled_entity.inv = LoadInventory(entity["inventory"]);
        break;
    case Entity::Type::NON_PLAYER_CHARACTER:
    default:
        p.controlled_entity.name = entity["name"];
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

    for (auto i : inventory["items"]) {
        inv.item.push_back(Item::Create(i));
    }

    return inv;
}

/* ----- CREATE ----- */

void Save::CreatePlayer(fs::path path, const Vector2D& pos) {
    json player = {
        {"name", "unknown"},
        {"hp", Entity::MAX_HP},

        {"mental power", 1}, // start with 1 mental power
        {"res power unlocked", false},
        {"exp power unlocked", false},
        {"shield power unlocked", false},

        {"island", "lost-temple"},
        {"x", pos.x},
        {"y", pos.y},

        {"state", Player::State::FREE},

        {"main quest", "An inmate"}, // will be changed
        {"side quests", json::array()},

        {"controlled entity", CreateDoll(pos.x, 2976, CreateInventory(1))}
    };

    std::ofstream outfile(path);
    outfile << std::setw(2) << player << std::endl;
    outfile.close();
}

void Save::CreateIsland_0(fs::path path) {
    json island = {
        {"name", "island-0"},
        {"width", 15},
        {"height", 11},
        {"tiles", {
            {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
            {10, 10, 10, 10,  5,  4,  4,  4,  4,  4,  4,  6, 10, 10, 10},
            {10, 10,  5,  4, 14,  1,  1,  1,  1,  1,  1, 13,  4,  6, 10},
            {10, 10,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3, 10},
            {10,  5, 14,  1, 28,  1,  1,  1,  1,  1,  1,  1,  1,  3, 10},
            {10,  2, 28, 28, 28,  1,  1,  1,  1,  1,  1,  1,  1,  3, 10},
            {10,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3, 10},
            {10,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3, 10},
            {10,  2,  1,  1,  1,  1,  1, 11,  7,  7,  7,  7,  7,  9, 10},
            {10,  8,  7,  7,  7,  7,  7,  9, 10, 10, 10, 10, 10, 10, 10},
            {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}
        }},
        {"portals", {
            CreatePortal(1280, 512, "island-1", 768, 896, 1)
        }},
        {"entities", {
            CreateDoll(432, 544, CreateInventory(1, {Item::ID::LAPIS_VITAE})),
            CreateDeadBody(1024, 384, Entity::Species::GOBLIN, Entity::Type::NON_PLAYER_CHARACTER, Entity::Behavior::STATIC, "unknown", CreateInventory(1)),
            CreateNPC(768, 896, Entity::Species::FAIRIES, Entity::Behavior::RANDOM_MOVEMENT, "Fairy", CreateInventory(1, {Item::ID::LAPIS_MAGICIS}), 1)
        }},
        {"items", {
            CreateItem(1024, 512, Item::ID::LAPIS_VITAE)
        }}
    };

    std::ofstream outfile(path);
    outfile << std::setw(2) << island << std::endl;
    outfile.close();
}

void Save::CreateIsland_1(fs::path path) {
    json island = {
        {"name", "island-1"},
        {"width", 30},
        {"height", 20},
        {"tiles", {
            {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  5,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  6},
            {10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  5,  4, 14,  1,  1,  1,  1,  1,  1,  1,  1, 19, 18, 18, 18, 18, 20,  1,  1,  3},
            {10, 10, 10, 10, 10, 10, 10,  5,  4,  4, 14,  1,  1,  1,  1,  1,  1,  1,  1, 19, 18, 27, 15, 15, 15, 15, 26, 20,  1,  3},
            {10, 10, 10, 10, 10,  5,  4, 14,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 16, 15, 15, 15, 15, 15, 15, 15, 17,  1,  3},
            {10, 10,  5,  4,  4, 14,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 19, 18, 27, 15, 15, 15, 15, 15, 15, 15, 26, 20,  3},
            {10, 10,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 16, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 17,  3},
            {10, 10,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 16, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 17,  3},
            {10, 10,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 22, 24, 15, 15, 15, 15, 15, 15, 15, 15, 15, 17,  3},
            {10,  5, 14,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 16, 15, 15, 15, 15, 15, 15, 15, 15, 15, 17,  3},
            {10,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 22, 21, 24, 15, 15, 15, 15, 15, 15, 15, 17,  3},
            {10,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 22, 21, 24, 15, 15, 15, 24, 21, 23,  3},
            { 5, 14,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 22, 21, 21, 21, 23,  1,  1,  3},
            { 2,  1,  1,  1,  1, 19, 18, 18, 18, 18, 20,  1, 11, 12,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3},
            { 2,  1,  1, 19, 18, 27, 15, 15, 15, 15, 17,  1,  3,  8, 12,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3},
            { 2,  1,  1, 16, 15, 15, 15, 15, 15, 15, 17,  1, 13,  6,  8,  7, 12,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 11,  9},
            { 2,  1,  1, 16, 15, 15, 15, 15, 15, 24, 23,  1,  1, 13,  3,  3, 14,  1,  1,  1,  1,  1,  1,  1,  1, 11,  7,  7,  9, 10},
            { 2,  1,  1, 22, 24, 15, 15, 15, 24, 23,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 11,  7,  9, 10, 10, 10, 10},
            { 2,  1,  1,  1, 22, 21, 21, 21, 23,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 11,  7,  9, 10, 10, 10, 10, 10, 10},
            { 2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 11,  7,  7,  9, 10, 10, 10, 10, 10, 10, 10, 10},
            { 8,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}
        }},
        {"portals", {
            CreatePortal(768, 896, "island-0", 1280, 512, 2)
        }},
        {"entities", {
            CreateNPC(1024, 512, Entity::Species::HUMAN, Entity::Behavior::STATIC, "Guide", CreateInventory(0), Entity::MAX_HP, true),
            CreateNPC(1280, 768, Entity::Species::GOBLIN, Entity::Behavior::RANDOM_MOVEMENT, "Traveler", CreateInventory(1, {Item::ID::LAPIS_MAGICIS})),
        }},
        {"items", json::array()}
    };

    std::ofstream outfile(path);
    outfile << std::setw(2) << island << std::endl;
    outfile.close();
}

void Save::CreateIsland_LostTemple(fs::path path, const Vector2D& dpos1, const Vector2D& dpos2, const Vector2D& dpos3) {
    json island = {
        {"name", "lost-temple"},
        {"width", 41},
        {"height", 41},
        {"tiles", {
          { 10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
          { 10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
          { 10,10,10,10,10,10,10,10,10,10,10,10,10,10,10, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
          { 10,10,10,10,10,10,10,10,10,10,10,10, 5, 4, 4,14, 1, 1, 1, 1, 1, 1, 1, 1, 1,13, 4, 4, 6,10,10,10,10,10,10,10,10,10,10,10,10},
          { 10,10,10,10,10,10,10,10,10,10, 5, 4,14, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,13, 4, 6,10,10,10,10,10,10,10,10,10,10},
          { 10,10,10,10,10,10,10,10,10, 5,14, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,13, 6,10,10,10,10,10,10,10,10,10},
          { 10,10,10,10,10,10,10,10, 5,14, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,13, 6,10,10,10,10,10,10,10,10},
          { 10,10,10,10,10,10,10, 5,14, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,13, 6,10,10,10,10,10,10,10},
          { 10,10,10,10,10,10, 5,14, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,13, 6,10,10,10,10,10,10},
          { 10,10,10,10,10, 5,14, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,13, 6,10,10,10,10,10},
          { 10,10,10,10, 5,14, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,13, 6,10,10,10,10},
          { 10,10,10,10, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,10,10,10,10},
          { 10,10,10, 5,14, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,13, 6,10,10,10},
          { 10,10,10, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28, 1, 1,28,28,28,28,28, 1, 1,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,10,10,10},
          { 10,10,10, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28,28, 1, 1, 1, 1, 1, 1, 1, 1, 1,28,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,10,10,10},
          { 10,10, 5,14, 1, 1, 1, 1, 1, 1, 1, 1, 1,28,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28,28, 1, 1, 1, 1, 1, 1, 1, 1, 1,13, 6,10,10},
          { 10,10, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28, 1,28, 1, 1, 1,28, 1,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,10,10},
          { 10,10, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28, 1, 1, 1,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,10,10},
          { 10,10, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28, 1, 1,28,28,28, 1, 1, 1,28,28,28, 1, 1,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,10,10},
          { 10,10, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,10,10},
          { 10,10, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,10,10},
          { 10,10, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,10,10},
          { 10,10, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28, 1, 1,28,28,28, 1, 1, 1,28,28,28, 1, 1,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,10,10},
          { 10,10, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28, 1, 1, 1,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,10,10},
          { 10,10, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28, 1,28, 1, 1, 1,28, 1,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,10,10},
          { 10,10, 8,12, 1, 1, 1, 1, 1, 1, 1, 1, 1,28,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28,28, 1, 1, 1, 1, 1, 1, 1, 1, 1,11, 9,10,10},
          { 10,10,10, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28,28, 1, 1, 1, 1, 1, 1, 1, 1, 1,28,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,10,10,10},
          { 10,10,10, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,28, 1, 1,28,28,28,28,28, 1, 1,28, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,10,10,10},
          { 10,10,10, 8,12, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,11, 9,10,10,10},
          { 10,10,10,10, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,10,10,10,10},
          { 10,10,10,10, 8,12, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,11, 9,10,10,10,10},
          { 10,10,10,10,10, 8,12, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,11, 9,10,10,10,10,10},
          { 10,10,10,10,10,10, 8,12, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,11, 9,10,10,10,10,10,10},
          { 10,10,10,10,10,10,10, 8,12, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,11, 9,10,10,10,10,10,10,10},
          { 10,10,10,10,10,10,10,10, 8,12, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,11, 9,10,10,10,10,10,10,10,10},
          { 10,10,10,10,10,10,10,10,10, 8,12, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,11, 9,10,10,10,10,10,10,10,10,10},
          { 10,10,10,10,10,10,10,10,10,10, 8, 7,12, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,11, 7, 9,10,10,10,10,10,10,10,10,10,10},
          { 10,10,10,10,10,10,10,10,10,10,10,10, 8, 7, 7,12, 1, 1, 1, 1, 1, 1, 1, 1, 1,11, 7, 7, 9,10,10,10,10,10,10,10,10,10,10,10,10},
          { 10,10,10,10,10,10,10,10,10,10,10,10,10,10,10, 8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
          { 10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
          { 10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10}
        }},
        {"portals", {
            CreatePortal(2560, 2560, "island-0", 1280, 512, 1)
        }},
        {"entities", json::array()},
        {"items", json::array()}
    };

    json::array_t entities = {
        CreateDoll(dpos1.x, dpos1.y, CreateInventory(1, {Item::ID::LAPIS_VITAE})),
        CreateDoll(dpos2.x, dpos2.y, CreateInventory(1)),
        CreateDoll(dpos3.x, dpos3.y, CreateInventory(1))
    };

    int n = 150;
    bool lapisMagicisPlaced = false;
    while (n > 0) {
        const int x = rand() % 41;
        const int y = rand() % 41;
        if (island["tiles"][y][x] == Tile::Type::GRASS) {
            n--;

            if (!lapisMagicisPlaced) {
                lapisMagicisPlaced = true;
                entities.push_back(CreateNPC(x*128,y*128,Entity::Species::GOBLIN,Entity::Behavior::RANDOM_MOVEMENT,"fairy",CreateInventory(1,{Item::ID::LAPIS_MAGICIS})));
            }
            else
                entities.push_back(CreateNPC(x*128,y*128,Entity::Species::FAIRIES,Entity::Behavior::RANDOM_MOVEMENT,"fairy",CreateInventory(1)));
        }
    }

    island["entities"] = entities;

    std::ofstream outfile(path);
    outfile << std::setw(2) << island << std::endl;
    outfile.close();
}

/* ----- SAVE ----- */

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

    data["main quest"] = player.curr_main_quest;
    data["side quests"] = player.curr_other_quests;

    switch (player.controlled_entity.type)
    {
    case Entity::Type::PLAYER:
        break;
    case Entity::Type::NON_PLAYER_CHARACTER:
        data["controlled entity"] = OrganizeNPC(player.controlled_entity);
        break;
    case Entity::Type::DOLL:
        data["controlled entity"] = OrganizeDoll(player.controlled_entity);
        break;
    default:
        data["controlled entity"] = CreateNoone();
        break;
    }

    std::ofstream outfile(path);
    outfile << std::setw(2) << data << std::endl;
    outfile.close();
}

void Save::SaveIsland(Island* island, fs::path path) {
    std::ifstream infile(path);
    json data;
    infile >> data;
    infile.close();

    std::vector<PortalStructure> pdata = island->getPortals();
    std::vector<json> portals;
    for (PortalStructure pd : pdata)
        portals.push_back(CreatePortal(pd.pos.x, pd.pos.y, pd.dest, pd.dest_pos.x, pd.dest_pos.y, pd.damage_level));
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

/* ----- STRUCTURE CREATION ----- */

json Save::CreateInventory(const int capacity, std::vector<int> items) {
    return {
        {"capacity", capacity},
        {"items", items}
    };
}

json Save::CreateItem(const int x, const int y, const int id) {
    return {
        {"x", x},
        {"y", y},
        {"id", id}
    };
}

json Save::CreatePortal(const int xp, const int yp, const std::string& dest, const int xd, const int yd, const int damage_level) {
    return {
        {"x", xp},
        {"y", yp},
        {"destination", dest},
        {"destinationX", xd},
        {"destinationY", yd},
        {"damage level", damage_level}
    };
}

json Save::CreateNoone() {
    return {
        {"type", Entity::Type::UNKNOWN},
        {"name", "noone"},
        {"inventory", {
            {"capacity", 0},
            json::array()
        }}
    };
}

json Save::CreateNPC(const int x, const int y, const int species, const int behavior, const std::string& name, const json& inventory, const int hp, const bool hasdialog) {
    return {
        {"type", Entity::Type::NON_PLAYER_CHARACTER},
        {"species", species},
        {"behavior", behavior},
        {"name", name},
        {"hp", hp},
        {"x", x},
        {"y", y},
        {"dialog", hasdialog},
        {"inventory", inventory}
    };
}

json Save::CreateDoll(const int x, const int y, const json& inv) {
    return {
        {"type", Entity::Type::DOLL},
        {"x", x},
        {"y", y},
        {"inventory", inv}
    };
}

json Save::CreateDeadBody(const int x, const int y, const int species, const int otype, const int obehavior, const std::string& oname, const json& oinv, const bool ohasdialog) {
    return {
        {"type", Entity::Type::DEAD_BODY},
        {"owner type", otype},
        {"species", species},
        {"behavior", obehavior},
        {"name", oname},
        {"x", x},
        {"y", y},
        {"inventory", oinv},
        {"dialog", ohasdialog}
    };
}

/* ----- STRUCTURE ORGANIZATION ----- */

json Save::OrganizeInventory(Inventory inventory) {
    std::vector<int> items;

    for (Item* i : inventory.item)
        items.push_back(i->id);

    return CreateInventory(inventory.capacity, items);
}

json Save::OrganizeItem(std::pair<Vector2D, int> i) {
    return CreateItem(i.first.x, i.first.y, i.second);
}

json Save::OrganizeNPC(EntityStructure npcs) {
    return CreateNPC(npcs.pos.x, npcs.pos.y, npcs.species, npcs.behavior, npcs.name, OrganizeInventory(npcs.inv), npcs.hp, npcs.npc_hasdialog);
}

json Save::OrganizeDoll(EntityStructure dolls) {
    return CreateDoll(dolls.pos.x, dolls.pos.y, OrganizeInventory(dolls.inv));
}

json Save::OrganizeDeadBody(EntityStructure s) {
    return CreateDeadBody(s.pos.x, s.pos.y, s.species, s.type2, s.behavior, s.name, OrganizeInventory(s.inv), s.npc_hasdialog);
}
