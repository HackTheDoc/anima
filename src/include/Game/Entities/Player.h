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
    SHIELD,
    NUMBER // just to count
};

struct PlayerStructure;

class Player : public Entity {
private:
    static Sprite* DEFAULT_SPRITE;
    static EntityCollider* DEFAULT_COLLIDER;
    static EntityDetector* DEFAULT_DETECTOR;

    bool hasUnlockedPower[Power::NUMBER];

    Entity *controlledEntity;
    int timeLeftBeforeHealthDecreasalOfControlledEntity;
    void setControlledEntityHealthDecreasalRate();

    void interactWithNPC(NPC *npc);
    void searchDeadBody(DeadBody* body);
    void resurrectDeadBody(DeadBody *body);

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

    void modifyNumenLevelBy(int ammount);

    void unlockPower(Power pid);
    bool haveUnlockedPower(Power pid);

    Inventory* parseInventory(const bool display_err_msg = false);
    Entity* parseControlledEntity();

    PlayerStructure getStructure();
};

struct PlayerStructure {
    std::string name;
    int hp;
    int numen_level;
    bool power[Power::NUMBER];

    Player::State state;

    Quest::ID curr_main_quest;
    std::vector<Quest::ID> curr_other_quests;

    std::string island;
    Vector2D pos;

    EntityStructure controlled_entity;
};
