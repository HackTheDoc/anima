#include "include/Save.h"
#include "include/serialization.h"

#include "include/Game/Game.h"
#include "include/KeyMap.h"
#include "include/Window.h"
#include "include/Manager.h"

#include <chrono>
#include <fstream>

bool Save::Auto = false;
std::string Save::pathToSaveFolder = "./data/";

/* ----- CONFIG ----- */
void Save::CreateConfig() {
    Struct::Config config{
    .autosave = true,
    .tutorial = true,
    .language = 0,
    .window_mode = 0,
    .worlds = {{
        {"World 1", "00:00:00"},
        {"World 2", "00:00:00"},
        {"World 3", "00:00:00"},
        {"World 4", "00:00:00"}
    }},
    .controls = {
            {"body resurrection", SDLK_m},
            {"interact", SDLK_e},
            {"inventory", SDLK_i},
            {"move down", SDLK_s},
            {"move left", SDLK_q},
            {"move right", SDLK_d},
            {"move up", SDLK_z},
            {"next answer", SDLK_UP},
            {"pause", SDLK_ESCAPE},
            {"power menu", SDLK_o},
            {"previous answer", SDLK_DOWN},
            {"quest menu", SDLK_l},
            {"take control", SDLK_p},
            {"valid dialog", SDLK_RETURN}
        }
    };

    serialize::config(config);
}

void Save::SaveConfig() {
    Struct::Config config = LoadConfig();

    config.autosave = Save::Auto;

    config.tutorial = Tutorial::activated;

    config.language = Window::language;

    config.window_mode = 0;
    if (Window::fullscreen)
        config.window_mode = SDL_WINDOW_FULLSCREEN_DESKTOP;

    config.controls = KeyMap::Export();

    serialize::config(config);
}

Struct::Config Save::LoadConfig() {
    if (!std::filesystem::exists("config")) CreateConfig();

    Struct::Config config = deserialize::config();

    return config;
}

/* ----- KEYMAP ----- */

void Save::Key(const std::string& ename, const SDL_KeyCode kcode) {
    Struct::Config config = LoadConfig();

    config.controls[ename] = kcode;

    serialize::config(config);
}

/* ----- GAME ----- */

void Save::PlayTime(const int wid) {
    std::chrono::time_point<std::chrono::system_clock> endTime = std::chrono::system_clock::now();
    std::chrono::nanoseconds currentSessionTime = endTime - Game::StartTime;

    Struct::Config config = LoadConfig();

    // parse previous chrono
    std::string timeString = config.worlds[wid-1].second;

    std::tm tm = {};
    std::istringstream ss(timeString);
    ss >> std::get_time(&tm, "%H:%M:%S");

    // prepare new string
    auto playtime = std::chrono::system_clock::from_time_t(std::mktime(&tm)) + currentSessionTime;
    std::time_t playtime_t = std::chrono::system_clock::to_time_t(playtime);
    std::stringstream nss;
    nss << std::put_time(std::localtime(&playtime_t), "%H:%M:%S");

    // saving it
    config.worlds[wid-1].second = nss.str();

    serialize::config(config);
}

std::pair<std::string, std::string> Save::GetWorldInfo(const int wid) {
    const Struct::Config config = LoadConfig();

    return config.worlds[wid-1];
}

bool Save::Exist(int sid) {
    fs::path path(pathToSaveFolder + "world-" + std::to_string(sid));

    return fs::exists(path);
}

bool Save::Create(int sid) {
    if (Exist(sid))
        return false;

    Struct::Game game;
    game.world_id = sid;

    // create player

    std::vector<Vector2D> doll_pos = {
        {2956, 2956}, // bottom right
        {2260, 2956}, // bottom left
        {2956, 2232}, // top right
        {2260, 2232}  // top left
    };
    int i = rand() % 4;
    game.player = CreatePlayer(doll_pos[i]);
    doll_pos.erase(doll_pos.cbegin() + i);

    // create islands
    i = rand() % 3;
    const Vector2D dpos1 = doll_pos[i];
    doll_pos.erase(doll_pos.cbegin() + i);

    i = rand() % 2;
    const Vector2D dpos2 = doll_pos[i];
    doll_pos.erase(doll_pos.cbegin() + i);

    const Struct::Island startingIsland = CreateIsland_LostTemple(dpos1, dpos2, doll_pos[0]);
    game.islands[startingIsland.name] = startingIsland;

    // test islands
    const Struct::Island testIsland0 = CreateIsland_0();
    game.islands[testIsland0.name] = testIsland0;
    const Struct::Island testIsland1 = CreateIsland_1();
    game.islands[testIsland1.name] = testIsland1;

    serialize::game(game, pathToSaveFolder + "world-" + std::to_string(sid));

    // save world name
    Struct::Config config = LoadConfig();
    config.worlds[sid - 1].first = Game::WorldName;
    serialize::config(config);

    return true;
}

bool Save::Erase(int sid) {
    if (!Exist(sid))
        return false;

    fs::remove(pathToSaveFolder + "world-" + std::to_string(sid));

    // reset world name and time
    Struct::Config config = LoadConfig();

    config.worlds[sid - 1] = std::make_pair("World " + std::to_string(sid), "00:00:00");

    serialize::config(config);

    return true;
}

bool Save::Update(int sid) {
    if (!Exist(sid))
        return false;

    Struct::Game game = Load(sid);

    game.player = Game::player->getStructure();

    const std::map<std::string, Struct::Island>& islands = Game::GetExploredIslandStructures();

    for (const auto& elt : islands)
        game.islands[elt.first] = elt.second;

    serialize::game(game, pathToSaveFolder + "world-" + std::to_string(sid));

    return true;
}

/* ----- LOAD ----- */

Struct::Game Save::Load(const int sid) {
    if (!Exist(sid)) Create(sid);

    Struct::Game game;
    deserialize::game(game, pathToSaveFolder + "world-" + std::to_string(sid));
    
    return game;
}

Struct::Player Save::LoadPlayer() {
    const Struct::Game game = Load(Game::WorldID);

    return game.player;
}

Struct::Island Save::LoadIsland(const std::string& island_name) {
    const Struct::Game game = Load(Game::WorldID);

    return game.islands.at(island_name);
}

/* ----- CREATE ----- */

Struct::Portal Save::CreatePortal(const int x, const int y, const std::string& dest, const int dx, const int dy, const int dmg_lvl) {
    return {
        .pos = {x,y},
        .dest = dest,
        .dest_pos = {dx,dy},
        .damage_level = dmg_lvl
    };
}

Struct::Map Save::CreateMap(const int width, const int height, const std::vector<std::vector<int>>& rmap) {
    Struct::Map map;
    map.width = width;
    map.height = height;

    map.tiles.resize(height);
    for (int y = 0; y < height; y++) {
        map.tiles[y].resize(width);
        for (int x = 0; x < width; x++)
            map.tiles[y][x] = (Tile::Type)rmap[y][x];
    }

    return map;
}

Struct::Item Save::CreateItem(const int x, const int y, const Item::ID id) {
    return { .pos = {x,y}, .id = id };
}

Struct::Inventory Save::CreateInventory(const size_t capacity, std::vector<Item::ID> items) {
    Struct::Inventory inv{ .capacity = capacity, .items = {} };

    for (size_t i = 0; i < items.size(); i++)
        inv.items.push_back(CreateItem(0, 0, items[i]));

    return inv;
}

Struct::Entity Save::CreateNPC(const int x, const int y, const EntitySpecies species, const EntityBehavior behavior, const std::string& name, const Struct::Inventory& inv, const int hp, const bool hasdialog) {
    const Struct::NPC npc{
        .species = species,
        .behavior = behavior,
        .name = name,
        .hp = hp,
        .pos = {x,y},
        .hasdialog = hasdialog,
        .inventory = inv
    };
    return Struct::Entity{ npc };
}

Struct::Entity Save::CreateDoll(const int x, const int y, const Struct::Inventory& inv) {
    const Struct::Doll doll{ .pos = {x,y}, .inventory = inv };
    return Struct::Entity{ doll };
}

Struct::Entity Save::CreateDeadBody(const int x, const int y, const EntitySpecies species, const EntityType otype, const EntityBehavior obehavior, const std::string& oname, const Struct::Inventory& inv, bool ohasdialog) {
    const Struct::DeadBody body{
        .species = species,
        .pos = {x,y},
        .inventory = inv,
        .o_type = otype,
        .o_behavior = obehavior,
        .o_name = oname,
        .o_hasdialog = ohasdialog
    };
    return Struct::Entity{ body };
}

Struct::Player Save::CreatePlayer(const Vector2D& pos) {
    const Struct::Player player{
        .name = "unknown",
        .hp = 1,
        .numen_level = 1,
        .power = {{false, false, false}},

        .state = Player::State::FREE,
        .tutorial_step = Tutorial::Step::OPEN_INVENTORY,

        .curr_main_quest = Quest::ID::AN_INMATE,
        .curr_other_quests = {},

#ifdef DEV_MOD
        .curr_island_on = "test island 0",
        .pos = {384, 768},
#else
        .curr_island_on = "lost temple",
        .pos = pos,
#endif

        .is_controlling_an_entity = true,
        .controlled_entity = CreateDoll(pos.x, pos.y, CreateInventory(1, {}))
    };

    return player;
}

Struct::Island Save::CreateIsland_0() {
    const Struct::Island island{
        .name = "test island 0",
        .map = CreateMap(15, 11, {
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
            }),
        .portals = {
            CreatePortal(1280, 512, "test island 1", 768, 896, 1)
        },
        .items = {
            CreateItem(1024, 512, Item::ID::LAPIS_VITAE)
        },
        .entities = {
            CreateDoll(432, 544, CreateInventory(1, {Item::ID::LAPIS_VITAE})),
            CreateNPC(768, 896, Entity::Species::FAIRIES, Entity::Behavior::RANDOM_MOVEMENT, "Fairy", CreateInventory(1), 1),
            CreateDeadBody(1024, 384, Entity::Species::GOBLIN, Entity::Type::NON_PLAYER_CHARACTER, Entity::Behavior::STATIC, "unknown", CreateInventory(1, {Item::ID::LAPIS_MAGICIS})),
        }
    };

    return island;
}

Struct::Island Save::CreateIsland_1() {
    return {
        .name = "test island 1",
        .map = CreateMap(30, 20, {
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
        }),
        .portals = {
            CreatePortal(768, 896, "island-0", 1280, 512, 2)
        },
        .items = {

        },
        .entities = {
            CreateNPC(1024, 512, Entity::Species::HUMAN, Entity::Behavior::STATIC, "Guide", CreateInventory(0), Entity::MAX_HP, true),
            CreateNPC(1280, 768, Entity::Species::GOBLIN, Entity::Behavior::RANDOM_MOVEMENT, "Traveler", CreateInventory(1, {Item::ID::LAPIS_MAGICIS}), Entity::MAX_HP),
        }
    };
}

Struct::Island Save::CreateIsland_LostTemple(const Vector2D& dpos1, const Vector2D& dpos2, const Vector2D& dpos3) {
    Struct::Island island{
        .name = "lost temple",
        .map = CreateMap(41, 41, {
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
        }),
        .portals = {
            CreatePortal(2560, 2560, "island-0", 1280, 512, 1)
        },
        .items = {},
        .entities = {}
    };

    std::vector<Struct::Entity> entities = {
        CreateDoll(dpos1.x, dpos1.y, CreateInventory(1, {Item::ID::LAPIS_VITAE})),
        CreateDoll(dpos2.x, dpos2.y, CreateInventory(1)),
        CreateDoll(dpos3.x, dpos3.y, CreateInventory(1))
    };

    int n = 150;
    bool lapisMagicisPlaced = false;
    while (n > 0) {
        const int x = rand() % 41;
        const int y = rand() % 41;
        if (island.map.tiles[y][x] == Tile::Type::GRASS) {
            n--;

            if (!lapisMagicisPlaced) {
                lapisMagicisPlaced = true;
                entities.push_back(CreateNPC(x * 128, y * 128, Entity::Species::FAIRIES, Entity::Behavior::RANDOM_MOVEMENT, "fairy", CreateInventory(1, { Item::ID::LAPIS_MAGICIS }), 1));
            }
            else
                entities.push_back(CreateNPC(x * 128, y * 128, Entity::Species::FAIRIES, Entity::Behavior::RANDOM_MOVEMENT, "fairy", CreateInventory(1), 1));
        }
    }

    island.entities = entities;

    return island;
}
