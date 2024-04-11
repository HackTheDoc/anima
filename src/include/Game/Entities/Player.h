#pragma once

#include "Entity.h"
#include "../Components/QuestSystem.h"

class NPC;
class DeadBody;

enum Interaction {
    NONE,
    USE,
    TAKE_CONTROL,
    RESURRECT
};

enum Power {
    BODY_CONTROL,
    BODY_RESURRECTION,
    BODY_EXPLOSION,
    SHIELD
};

namespace Struct {
    struct Player;
};

class Player : public Entity {
private:
    static Sprite* DEFAULT_SPRITE;
    static EntityCollider* DEFAULT_COLLIDER;
    static EntityDetector* DEFAULT_DETECTOR;

    bool hasUnlockedPower[4];

    Entity* controlledEntity;
    int timeLeftBeforeHealthDecreasalOfControlledEntity;
    void setHealthDecreasalRate();

    void interactWithNPC(NPC* npc);
    void searchDeadBody(DeadBody* body);
    void resurrectDeadBody(DeadBody* body);

    // become a spirit;
    void reset();

public:
    enum State {
        FREE,
        IN_DIALOG,

        DEAD
    };
    State state;

    static QuestSystem* quest;

    Interaction interaction;
    NPC* interactingWith;

    Player();
    ~Player();

    void init() override;
    void update() override;
    void draw() override;
    void kill() override;

    void interactWith(Entity* e);
    void takeControlOf(Entity* e);
    void releaseControledEntity();

    void modifyNumenLevelBy(const int ammount);

    void unlockPower(const Power pid);
    bool haveUnlockedPower(const Power pid);

    Inventory* parseInventory(const bool displayErrorMessage = false);
    void setControlledEntity(Entity* e);
    Entity* parseControlledEntity();

    Struct::Player getStructure();
};
