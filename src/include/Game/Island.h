#pragma once

#include <string>
#include <vector>

#include "Entities/Entities.h"

#include "Map/Map.h"
#include "Map/Structures/Structures.h"

namespace Struct {
    struct Island;
};

class Island {
public:
    Map* map;
    
    Island(const std::string& name);
    ~Island();

    void init();
    void update();
    void render();
    void destroy();

    void getSize(int* w, int* h);
    std::string getName();

    void addItem(const Vector2D& pos, Item* i);

    void addNPC(const Vector2D& pos, const Entity::Species species, const Entity::Behavior behavior, const std::string& name, const int hp, const bool hasdialog, const Inventory& inv);
    void addDoll(const Vector2D& pos, const Inventory& inv);
    void addDeadBody(const Entity::Species species, const Vector2D& pos, const Inventory& inv, const Entity::Type otype, const std::string& oname, const bool ohasDialog, const Entity::Behavior obehavior);
    void addEntity(Entity* e);
    void removeEntity(Entity* e);

    Struct::Island getStructure();

private:
    std::string name;
    
    std::vector<Portal*> portals;
    std::vector<Door*> doors;
    std::vector<Entity*> entities;
    std::vector<Item*> items;

    void updateFreeState();
    void updateInDollState();
};
