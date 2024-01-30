#pragma once

#include <string>
#include <vector>

#include "Entities/Entities.h"

#include "Map/Map.h"
#include "Map/Structures/Portal.h"

class Island {
public:
    Map* map;
    
    Island(std::string name);
    ~Island();

    void init();
    void update();
    void render();
    void destroy();

    void getSize(int* w, int* h);
    std::string getName();

    void addPortal(int x, int y, std::string dest, int destX, int destY, bool opened);
    void addItem(int x, int y, Item::ID id);
    void addItem(Vector2D pos, Item* i);
    void addNPC(Entity::Species species, std::string name, int hp, int x, int y, bool haveDialog, NPC::Behavior behavior);
    void addNPC(Entity::Species species, std::string name, int hp, int x, int y, bool haveDialog, NPC::Behavior behavior, Inventory inv);
    void addDoll(int x, int y, Inventory inv);
    void addDeadBody(Entity::Species species, Entity::Type type, std::string name, int x, int y, bool haveDialog, NPC::Behavior behavior);
    
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
