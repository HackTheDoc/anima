#include "include/Game/Entities/Player.h"

#include "include/Game/Game.h"
#include "include/Game/Components/Collision.h"
#include "include/Game/Entities/Entities.h"

#include "include/Save.h"

QuestSystem* Player::quest = nullptr;

Sprite* Player::DEFAULT_SPRITE = nullptr;
EntityCollider* Player::DEFAULT_COLLIDER = nullptr;
EntityDetector* Player::DEFAULT_DETECTOR = nullptr;

Player::Player() {
    type = Type::PLAYER;
    inventory.capacity = 0;
}

Player::~Player() {}

void Player::init() {
    PlayerStructure data = Save::LoadPlayer(Game::WorldID);

    Entity::init();

    DEFAULT_SPRITE = new Sprite(this);
    DEFAULT_SPRITE->init("player", 6);
    sprite = DEFAULT_SPRITE;

    DEFAULT_COLLIDER = new EntityCollider(this);
    collider = DEFAULT_COLLIDER;

    DEFAULT_DETECTOR = new EntityDetector(this);
    detector = DEFAULT_DETECTOR;

    name = data.name;
    hp = data.hp;

    // powers
    numenLevel = data.numen_level;
    hasUnlockedPower[Power::BODY_CONTROL] = true;
    hasUnlockedPower[Power::BODY_RESURRECTION] = data.power[Power::BODY_RESURRECTION];
    hasUnlockedPower[Power::BODY_EXPLOSION] = data.power[Power::BODY_EXPLOSION];
    hasUnlockedPower[Power::SHIELD] = data.power[Power::SHIELD];

    // state & quests
    state = data.state;

    quest = new QuestSystem(data.curr_main_quest);
    for (std::string q : data.curr_other_quests)
        quest->addQuest(q);

    // pos & speed
    position = data.pos;
    walkSpeed = 6;

    // interactions
    interaction = Interaction::NONE;
    interactingWith = nullptr;

    if (data.controlled_entity.type == Entity::Type::NON_PLAYER_CHARACTER) {
        NPC* npc = new NPC(data.controlled_entity.name, data.controlled_entity.species, data.controlled_entity.behavior, data.controlled_entity.inv);
        npc->init();
        npc->setPosition(data.controlled_entity.pos.x, data.controlled_entity.pos.y);
        npc->haveDialog = data.controlled_entity.npc_hasdialog;
        npc->hp = data.controlled_entity.hp;

        this->sprite = npc->sprite;
        this->sprite->linkTo(this);

        this->controlledEntity = npc;
        npc->controlled = true;
        this->controlled = true;

        this->walkSpeed = npc->walkSpeed;
    }

    else if (data.controlled_entity.type == Entity::Type::DOLL) {
        Doll* doll = new Doll(data.controlled_entity.inv);
        doll->init();
        doll->setPosition(data.controlled_entity.pos.x, data.controlled_entity.pos.y);

        this->sprite = doll->sprite;
        this->sprite->linkTo(this);

        this->controlledEntity = doll;
        doll->controlled = true;
        this->controlled = true;

        this->walkSpeed = doll->walkSpeed;
    }
}

void Player::update() {
    Entity::update();

    if (controlledEntity == nullptr || controlledEntity->type != Entity::Type::NON_PLAYER_CHARACTER || controlledEntity->immortal)
        return;

    timeLeftBeforeHealthDecreasalOfControlledEntity--;

    if (timeLeftBeforeHealthDecreasalOfControlledEntity > 0)
        return;

    controlledEntity->hp--;
    setControlledEntityHealthDecreasalRate();

    // if the controlled entity is dead
    if (controlledEntity->hp <= 0) {
        UI::AddPopUp("YOUR BODY DIED");

        bool hasdialog = false;
        if (controlledEntity->type == Entity::Type::NON_PLAYER_CHARACTER) {
            NPC* npc = static_cast<NPC*>(controlledEntity);
            hasdialog = npc->haveDialog;
        }

        Game::island->addDeadBody(
            controlledEntity->species, 
            controlledEntity->type, 
            controlledEntity->name,
            position.x,
            position.y,
            hasdialog,
            controlledEntity->behavior,
            controlledEntity->inventory
        );        
        
        controlledEntity->kill();
        reset();
    }
}

void Player::draw() {
    Entity::draw();
}

void Player::kill() {
    Entity::kill();

    controlledEntity = nullptr;
    quest = nullptr;
}

void Player::interactWith(Entity* e) {
    switch (e->type) {
    case Entity::Type::NON_PLAYER_CHARACTER:
        if (NPC* npc = dynamic_cast<NPC*>(e))
            if (npc->haveDialog)
                Game::ui->useHint(" - Talk", e);
        break;
    case Entity::Type::DEAD_BODY:
        if (controlled)
            Game::ui->useHint(" - Search", e);
        else if (haveUnlockedPower(Power::BODY_RESURRECTION))
            Game::ui->useHint(" - Resurrect", e);
    default:
        break;
    }

    switch (interaction) {
    case Interaction::USE:
        if (NPC* npc = dynamic_cast<NPC*>(e))
            interactWithNPC(npc);
        break;
    case Interaction::TAKE_CONTROL:
        takeControlOf(e);
        break;
    case Interaction::RESURRECT:
        if (DeadBody* body = dynamic_cast<DeadBody*>(e))
            resurrectEntity(body);
        break;
    default:
        break;
    }

    interaction = Interaction::NONE;
}

void Player::interactWithNPC(NPC* npc) {
    Game::ui->useHint("NONE");

    if (this->position.x < npc->position.x)
        npc->setFlip(SDL_FLIP_HORIZONTAL);
    else
        npc->setFlip(SDL_FLIP_NONE);

    if (npc->haveDialog)
        npc->startDialog();
}

void Player::takeControlOf(Entity* e) {
    if (e->type == Entity::Type::DEAD_BODY) return;

    // check if the player have enough mental power
    if (e->numenLevel > this->numenLevel) {
        UI::AddPopUp("YOU LACK NUMEN TOKENS");
        return;
    }

    this->sprite = e->sprite;
    this->sprite->linkTo(this);

    this->collider = e->collider;
    this->collider->setOwner(this);

    this->detector = e->detector;
    this->detector->setOwner(this);

    this->position = e->position;

    Game::island->removeEntity(e);

    this->controlledEntity = e;
    e->controlled = true;
    this->controlled = true;

    setControlledEntityHealthDecreasalRate();

    this->walkSpeed = e->walkSpeed;
    playAnimation("Idle");
}

void Player::releaseControledEntity() {
    controlledEntity->sprite->linkTo(controlledEntity);

    controlledEntity->collider->setOwner(controlledEntity);

    controlledEntity->detector->setOwner(controlledEntity);

    controlledEntity->position = this->position;
    controlledEntity->resetMovement();

    controlledEntity->controlled = false;

    Game::island->addEntity(controlledEntity);

    reset();
}

void Player::resurrectEntity(DeadBody* body) {
    if (body->numenLevel > this->numenLevel) {
        UI::AddPopUp("YOU LACK MENTAL POWER");
        return;
    }

    Game::ui->useHint("NONE");

    Game::island->removeEntity(body);

    switch (body->ownerType) {
    case Entity::Type::NON_PLAYER_CHARACTER:
        Game::island->addNPC(body->species, body->name, Entity::MAX_HP, body->position.x, body->position.y, body->ownerHasDialog, body->behavior, body->inventory);
        break;
    default:
        break;
    }

    modifyNumenLevelBy(-3);
}

void Player::modifyNumenLevelBy(int ammount) {
    numenLevel = std::max(0, numenLevel + ammount);
}

void Player::unlockPower(Power pid) {
    hasUnlockedPower[pid] = true;
    modifyNumenLevelBy(-5);
}

bool Player::haveUnlockedPower(Power pid) {
    return hasUnlockedPower[pid];
}

Inventory* Player::parseInventory(const bool display_err_msg) {
    if (controlledEntity == nullptr) {
        if (display_err_msg)
            UI::AddPopUp("YOU CANNOT OPEN YOUR INVENTORY");
        return nullptr;
    }
    else if (controlledEntity->inventory.capacity == 0) {
        if (display_err_msg)
            UI::AddPopUp("THIS ENTITY DOES NOT HAVE AN INVENTORY");
        return nullptr;
    }
    else return &controlledEntity->inventory;
}

Entity* Player::parseControlledEntity() {
    return controlledEntity;
}

PlayerStructure Player::getStructure() {
    EntityStructure e;
    e.type = Entity::Type::UNKNOWN;
    e.name = "noone";

    PlayerStructure structure;

    structure.name = name;
    structure.hp = hp;

    structure.numen_level = numenLevel;
    structure.power[Power::BODY_CONTROL] = hasUnlockedPower[Power::BODY_CONTROL];
    structure.power[Power::BODY_RESURRECTION] = hasUnlockedPower[Power::BODY_RESURRECTION];
    structure.power[Power::BODY_EXPLOSION] = hasUnlockedPower[Power::BODY_EXPLOSION];
    structure.power[Power::SHIELD] = hasUnlockedPower[Power::SHIELD];

    structure.island = Game::island->getName();

    structure.pos = position;

    structure.controlled_entity = e;

    if (state == State::IN_DIALOG)
        structure.state = State::FREE;

    structure.curr_main_quest = quest->main.title;
    for (Quest q : quest->others)
        structure.curr_other_quests.push_back(q.title);

    if (controlledEntity != nullptr) {
        switch (controlledEntity->type) {
        case Entity::Type::NON_PLAYER_CHARACTER:
            structure.controlled_entity = static_cast<NPC*>(controlledEntity)->getStructure();
            break;
        case Entity::Type::DOLL:
            structure.controlled_entity = static_cast<Doll*>(controlledEntity)->getStructure();
            break;
        case Entity::Type::PLAYER:
        case Entity::Type::UNKNOWN:
        default:
            structure.controlled_entity.type = Entity::Type::UNKNOWN;
            break;
        }
    }

    return structure;
}

/// TODO: define the health decreasal rate for each species
void Player::setControlledEntityHealthDecreasalRate() {
    if (controlledEntity == nullptr || controlledEntity->type != Entity::Type::NON_PLAYER_CHARACTER) {
        timeLeftBeforeHealthDecreasalOfControlledEntity = 0;
        return;
    }

    switch (controlledEntity->species) {
    case Entity::Species::FAIRIES:
        timeLeftBeforeHealthDecreasalOfControlledEntity = 300;
        break;
    case Entity::Species::GOBLIN:
        timeLeftBeforeHealthDecreasalOfControlledEntity = 450;
        break;
    case Entity::Species::HUMAN:
    default:
        timeLeftBeforeHealthDecreasalOfControlledEntity = 600;
        break;
    }
}

void Player::reset() {
    sprite = DEFAULT_SPRITE;
    collider = DEFAULT_COLLIDER;
    detector = DEFAULT_DETECTOR;

    controlledEntity = nullptr;
    controlled = false;

    walkSpeed = 6;
}
