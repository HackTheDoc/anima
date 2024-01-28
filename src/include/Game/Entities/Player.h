#pragma once

#include "Entity.h"

class NPC;
class DeadBody;

enum Interaction
{
    NONE,
    USE,
    TAKE_CONTROL,
    RESURRECT
};

enum Power
{
    BODY_CONTROL,
    BODY_RESURRECTION,
    BODY_EXPLOSION,
    SHIELD,
    NUMBER // just to count
};

struct PlayerStructure;

class Player : public Entity
{
private:
    static Sprite *DEFAULT_SPRITE;

    bool hasUnlockedPower[Power::NUMBER];

    Entity *controlledEntity;

    void interactWithNPC(NPC *npc);

public:
    enum State
    {
        FREE,
        IN_DIALOG
    };

    State state;

    Interaction interaction;
    NPC *interactingWith;

    Player();
    ~Player();

    void init() override;
    void update() override;
    void draw() override;
    void kill() override;

    void interactWith(Entity *e);
    void takeControlOf(Entity *e);
    void releaseControledEntity();
    void resurrectEntity(DeadBody *body);

    void modifyNumenLevelBy(int ammount);

    void unlockPower(Power pid);
    bool haveUnlockedPower(Power pid);

    Inventory* parseInventory();
    Entity* parseControlledEntity();

    PlayerStructure getStructure();
};

struct PlayerStructure
{
    std::string name;
    int hp;
    int numen_level;
    bool power[Power::NUMBER];

    Player::State state;

    std::string island;
    Vector2D pos;

    EntityStructure controlled_entity;
};
