#pragma once

#include "../Components/Vector2D.h"
#include "../Components/Sprite.h"
#include "../Components/EntityCollider.h"
#include "../Components/EntityDetector.h"
#include "../Components/Inventory.h"

struct EntityStructure;

class Entity
{
public:
    static const int MAX_HP;

    enum Type
    {
        PLAYER,
        NON_PLAYER_CHARACTER,
        DOLL,
        DEAD_BODY,

        UNKNOWN // literrally unknown
    };
    Entity::Type type;

    enum Species
    {
        HUMAN,
        GOBLIN
    };
    Entity::Species species;

    Sprite *sprite;

    EntityCollider *collider;
    EntityDetector *detector;

    int hp;
    int height, width;

    Vector2D position;
    int hSpeed, vSpeed;
    int walkSpeed;

    Inventory inventory;

    /// @brief very important for the usage of power from the player
    int numenLevel;
    bool controlled;

    std::string name;

    bool immortal;

    Entity();
    ~Entity();

    virtual void init();
    virtual void update();
    virtual void draw();
    virtual void kill();

    void setPosition(int x, int y);
    void setPosition(Vector2D pos);
    void playAnimation(std::string animationName);
    void setFlip(SDL_RendererFlip flipMod);

    void resetMovement();

    void startInteraction();
    void closeIntereaction();

    void addItemToInventory(Item::ID id);
    bool addItemToInventory(Item* item);

    EntityStructure getStructure();

    static int GetMentalPower(Entity::Species species);
};

struct EntityStructure
{
    Entity::Type type;
    Entity::Type type2;

    Entity::Species species;

    std::string name;
    int hp;

    Vector2D pos;

    Inventory inv;

    bool npc_hasdialog;
};
