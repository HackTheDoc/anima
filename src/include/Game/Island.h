#pragma once

#include <string>
#include <vector>

#include "Entities/Entities.h"

#include "Map/Map.h"
#include "Map/Structures/Portal.h"

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

    void addPortal(const int x, const int y, const std::string& dest, const int destX, const int destY, const int damage_lvl);
    void addItem(const int x, const int y, const Item::ID id);
    void addItem(const Vector2D& pos, Item* i);
    void addNPC(Entity::Species species, const std::string& name, const int hp, const int x, const int y, const bool haveDialog, const Entity::Behavior behavior);
    void addNPC(Entity::Species species, const std::string& name, const int hp, const int x, const int y, const bool haveDialog, const Entity::Behavior behavior, const Inventory& inv);
    void addDoll(const int x, const int y, const Inventory& inv);
    void addDeadBody(const Entity::Species species, const Entity::Type type, const std::string& name, const int x, const int y, const bool haveDialog, const Entity::Behavior behavior, const Inventory& inv);
    
    void removeEntity(Entity* e);
    void addEntity(Entity* e);

    std::vector<PortalStructure> getPortals();
    std::vector<EntityStructure> getEntities();
    std::vector<std::pair<Vector2D, Item::ID>> getItems();

private:
    std::string name;
    std::vector<Portal*> portals;
    std::vector<Entity*> entities;
    std::vector<Item*> items;

    void updateFreeState();
    void updateInDollState();
};
