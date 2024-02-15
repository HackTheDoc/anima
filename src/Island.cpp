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
    const Struct::Island data = Save::LoadIsland(name);

    // LOADING MAP
    map->init(data.map);

    // LOADING PORTALS
    for (const Struct::Portal& portal : data.portals) {
        Portal* p = new Portal();
        p->init(portal);
        portals.push_back(p);
    }

    // LOADING ITEMS
    for (const Struct::Item& item : data.items) {
        Item* i = Item::Create(item.id);
        i->collider->place(item.pos);
        items.push_back(i);
    }

    // LOADING ENTITIES
    struct Visitor {
        Island* island;

        void operator()(const Struct::NPC& data) {
            island->addNPC(data.pos, data.species, data.behavior, data.name, data.hp, data.hasdialog, data.inventory);
        }

        void operator()(const Struct::Doll& data) {
            island->addDoll(data.pos, data.inventory);
        }

        void operator()(const Struct::DeadBody& data) {
            island->addDeadBody(data.species, data.pos, data.inventory, data.o_type, data.o_name, data.o_hasdialog, data.o_behavior);
        }
    };
    Visitor visitor{this};

    for (const auto& entity : data.entities)
        std::visit(visitor, entity.e);
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

void Island::addItem(const Vector2D& pos, Item* i) {
    i->collider->position = pos;
    items.push_back(i);
}

void Island::addNPC(const Vector2D& pos, const Entity::Species species, const Entity::Behavior behavior, const std::string& name, const int hp, const bool hasdialog, const Inventory& inv) {
    NPC* npc = new NPC(name, species, behavior, inv);
    npc->init();
    npc->haveDialog = hasdialog;
    npc->hp = hp;
    npc->setPosition(pos);
    addEntity(npc);
}

void Island::addDoll(const Vector2D& pos, const Inventory& inv) {
    Doll* doll = new Doll(inv);
    doll->init();
    doll->setPosition(pos);
    addEntity(doll);
}

void Island::addDeadBody(const Entity::Species species, const Vector2D& pos, const Inventory& inv, const Entity::Type otype, const std::string& oname, const bool ohasDialog, const Entity::Behavior obehavior) {
    DeadBody* body = new DeadBody(species);
    body->init();
    body->ownerType = otype;
    body->name = oname;
    body->setPosition(pos);
    body->ownerHasDialog = ohasDialog;

    /// WARNING: may change
    switch (otype) {
    case Entity::Type::NON_PLAYER_CHARACTER:
        body->numenLevel = 1;
        body->behavior = obehavior;
        break;
    default:
        body->numenLevel = INT32_MAX;
        break;
    }

    body->inventory = inv;
    addEntity(body);
}

void Island::addEntity(Entity* e) {
    e->update();
    entities.push_back(e);
}

void Island::removeEntity(Entity* e) {
    entities.erase(std::remove(entities.begin(), entities.end(), e), entities.end());
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

Struct::Island Island::getStructure() {
    Struct::Island island;
    island.name = name;

    island.map = map->getStructure();
    
    island.portals.resize(portals.size());
    for (size_t i = 0; i < portals.size(); i++)
        island.portals[i] = portals[i]->getStructure();
    
    island.items.resize(items.size());
    for (size_t i = 0; i < items.size(); i++)
        island.items[i] = items[i]->getStructure();
    
    island.entities.resize(entities.size());
    for (size_t i = 0; i < entities.size(); i++) {
        switch (entities[i]->type) {
        case Entity::Type::NON_PLAYER_CHARACTER:
            if (NPC* npc = dynamic_cast<NPC*>(entities[i]))
                island.entities[i] = npc->getStructure();
            break;
        case Entity::Type::DOLL:
            if (Doll* doll = dynamic_cast<Doll*>(entities[i]))
                island.entities[i] = doll->getStructure();
            break;
        case Entity::Type::DEAD_BODY:
            if (DeadBody* body = dynamic_cast<DeadBody*>(entities[i]))
                island.entities[i] = body->getStructure();
            break;
        default:
            break;
        }
    }

    return island;
}
