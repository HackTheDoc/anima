#include "include/Game/Island.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <algorithm>

#include "include/Save.h"

#include "include/Game/Game.h"
#include "include/Game/Components/Collision.h"

Island::Island(const std::string& name)
    : name(name)
    { map = new Map(); }

Island::~Island() {}

void Island::init() {
    nlohmann::json data = Save::LoadIsland(Game::WorldID, name);

    name = data["name"];

    // LOADING MAP
    map->init(data["width"], data["height"]);
    const auto& tile = data["tiles"];
    for (int y = 0; y < map->getHeight(); y++)
        for (int x = 0; x < map->getWidth(); x++)
            map->setTile(x, y, tile[y][x]);

    // LOADING PORTALS
    for (const auto& portal : data["portals"]) {
        addPortal(
            portal["x"],
            portal["y"],
            portal["destination"],
            portal["destinationX"],
            portal["destinationY"],
            portal["damage level"]);
    }

    // LOADING ITEMS
    for (const auto& item : data["items"]) {
        addItem(
            item["x"],
            item["y"],
            item["id"]);
    }

    // LOADING ENTITIES
    for (const auto& entity : data["entities"]) {
        Entity::Type t = entity["type"];
        switch (t) {
        case Entity::Type::PLAYER:
            Game::player->setPosition(entity["x"], entity["y"]);
            break;
        case Entity::Type::NON_PLAYER_CHARACTER:
            addNPC(entity["species"], entity["name"], entity["hp"], entity["x"], entity["y"], entity["dialog"], entity["behavior"], Save::LoadInventory(entity["inventory"]));
            break;
        case Entity::Type::DOLL:
            addDoll(entity["x"], entity["y"], Save::LoadInventory(entity["inventory"]));
            break;
        case Entity::DEAD_BODY:
            addDeadBody(entity["species"], entity["owner type"], entity["name"], entity["x"], entity["y"], entity["dialog"], entity["behavior"], Save::LoadInventory(entity["inventory"]));
            break;
        default:
            break;
        }
    }
}

void Island::update() {
    switch (Game::player->state) {
    case Player::State::FREE:
        updateFreeState();
        break;
    case Player::State::IN_DIALOG:
    default:
        break;
    }
}

void Island::render() {
    map->render();

    for (const auto& p : portals) {
        p->draw();
    }

    for (const auto& i : items) {
        i->drawIconAt(i->collider->rect);
        i->collider->draw();
    }

    for (const auto& e : entities) {
        if (!e->controlled)
            e->draw();
    }
}

void Island::destroy() {
    for (const auto& p : portals) {
        p->destroy();
    }
    portals.clear();

    for (const auto& e : entities) {
        e->kill();
    }
    entities.clear();

    map->destroy();
    delete map;
    map = nullptr;
}

void Island::getSize(int* w, int* h) {
    *w = map->getWidth() * Tile::SIZE;
    *h = map->getHeight() * Tile::SIZE;
}

std::string Island::getName() {
    return name;
}

void Island::addPortal(const int x, const int y, const std::string& dest, const int destX, const int destY, const int damage_lvl) {
    Portal* p = new Portal();
    p->init(
        x,
        y,
        dest,
        destX + (Tile::SIZE - Game::player->collider->rect.w) / 2,
        destY + (Tile::SIZE - Game::player->collider->rect.h) / 2,
        damage_lvl
    );
    portals.push_back(p);
}

void Island::addItem(const int x, const int y, const Item::ID id) {
    Item* i = Item::Create(id);

    if (i == nullptr)
        return;

    i->collider->place(x, y);

    items.push_back(i);
}

void Island::addItem(const Vector2D& pos, Item* i) {
    i->collider->position = pos;
    items.push_back(i);
}

void Island::addNPC(const Entity::Species species, const std::string& name, const int hp, const int x, const int y, const bool hasDialog, const Entity::Behavior behavior) {
    NPC* npc = new NPC(name, species, behavior);
    npc->init();
    npc->setPosition(x, y);
    npc->haveDialog = hasDialog;
    npc->hp = hp;
    addEntity(npc);
}

void Island::addNPC(const Entity::Species species, const std::string& name, const int hp, const int x, const int y, const bool hasDialog, const Entity::Behavior behavior, const Inventory& inv) {
    NPC* npc = new NPC(name, species, behavior, inv);
    npc->init();
    npc->setPosition(x, y);
    npc->haveDialog = hasDialog;
    npc->hp = hp;
    addEntity(npc);
}

void Island::addDoll(const int x, const int y, const Inventory& inv) {
    Doll* doll = new Doll(inv);
    doll->init();
    doll->setPosition(x, y);
    addEntity(doll);
}

void Island::addDeadBody(const Entity::Species species, const Entity::Type type, const std::string& name, const int x, const int y, const bool haveDialog, const Entity::Behavior behavior, const Inventory& inv) {
    DeadBody* b = new DeadBody(species);
    b->init();
    b->ownerType = type;
    b->name = name;
    b->setPosition(x, y);
    b->ownerHasDialog = haveDialog;

    /// WARNING: may change
    switch (type) {
    case Entity::Type::NON_PLAYER_CHARACTER:
        b->numenLevel = 1;
        b->behavior = behavior;
        break;
    default:
        b->numenLevel = INT32_MAX;
        break;
    }

    b->inventory = inv;

    entities.push_back(b);
}

void Island::updateFreeState() {
    map->update();

    for (const auto& e : entities) {
        if (e->controlled)
            continue;

        if (Collision::AABB(Game::player->detector, e->detector)) {
            Game::player->interactWith(e);
        }
        e->update();
    }

    for (const auto& p : portals) {
        p->update();
            
        if (Collision::AABB(Game::player->detector, p->collider)) {
            if (p->isRepaired()) {
                Game::ui->hideHint(" - Repair");
            }
            else
            {
                Game::ui->useHint(" - Repair", p);
                if (Game::player->interaction == Interaction::USE)
                    p->repair();
            }
        }

        if (Collision::AABB(Game::player->collider, p->collider) && Game::player->interaction == Interaction::USE)
            p->use();
    }

    for (const auto& i : items) {
        i->collider->update();

        if (Collision::AABB(Game::player->detector, i->collider)) {
            Game::ui->useHint(" - Pick up", i->collider);

            if (Window::event.raised(Event::ID::INTERACT)) {
                Entity* e = Game::player->parseControlledEntity();

                if (e == nullptr)
                    UI::AddPopUp("YOU CANNOT PICK UP ITEMS IN YOUR CURRENT STATE");
                else if (e->addItemToInventory(i)) {
                    items.erase(std::remove(items.begin(), items.end(), i), items.end());
                    Game::ui->hideHint("- Pick up");
                    Game::player->interaction = Interaction::NONE;
                }
                else {
                    UI::AddPopUp("INVENTORY FULL");
                }
            }
        }
    }
}

void Island::updateInDollState() {
    for (const auto& e : entities) {
        e->update();
    }
}

void Island::addEntity(Entity* e) {
    entities.push_back(e);
}

void Island::removeEntity(Entity* e) {
    entities.erase(std::remove(entities.begin(), entities.end(), e), entities.end());
}

std::vector<PortalStructure> Island::getPortals() {
    std::vector<PortalStructure> pstructures;
    for (auto p : portals)
        pstructures.push_back(p->getStructure());

    return pstructures;
}

std::vector<EntityStructure> Island::getEntities() {
    std::vector<EntityStructure> estructures;
    for (auto e : entities) {
        switch (e->type) {
        case Entity::Type::NON_PLAYER_CHARACTER:
            estructures.push_back(static_cast<NPC*>(e)->getStructure());
            break;
        case Entity::Type::DOLL:
            estructures.push_back(static_cast<Doll*>(e)->getStructure());
            break;
        case Entity::Type::DEAD_BODY:
            estructures.push_back(static_cast<DeadBody*>(e)->getStructure());
        case Entity::Type::PLAYER:
        case Entity::Type::UNKNOWN:
        default:
            break;
        }
    }

    return estructures;
}

std::vector<std::pair<Vector2D, Item::ID>> Island::getItems() {
    std::vector<std::pair<Vector2D, Item::ID>> is;

    for (auto i : items)
        is.push_back(std::make_pair(i->collider->position, i->id));

    return is;
}
