#pragma once

#include "../Components/Vector2D.h"
#include "../Components/Sprite.h"
#include "../Components/EntityCollider.h"
#include "../Components/EntityDetector.h"
#include "../Components/Inventory.h"

namespace Struct {
    struct Entity;
};

class Entity {
public:
    static const int MAX_HP;

    enum Type {
        PLAYER,
        NON_PLAYER_CHARACTER,
        DOLL,
        DEAD_BODY,

        UNKNOWN // literrally unknown
    };
    Type type;

    enum Species {
        HUMAN,
        FAIRIES,
        GOBLIN
    };
    Species species;

    enum Behavior {
        STATIC,
        RANDOM_MOVEMENT
    };
    Behavior behavior;

    Sprite* sprite;

    EntityCollider* collider;
    EntityDetector* detector;

    int hp;
    int height, width;

    Vector2D position, velocity;
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
    void reverseMovement();

    void startInteraction();
    void closeIntereaction();

    void addItemToInventory(Item::ID id);
    bool addItemToInventory(Item* item);

    bool has_died();

    static int GetMentalPower(Entity::Species species);

protected:
    void randomMovement();
};
