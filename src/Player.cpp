#include "include/Game/Entities/Player.h"

#include "include/Game/Game.h"
#include "include/Game/Components/Collision.h"
#include "include/Game/Entities/Entities.h"

#include "include/Save.h"

int sign(int n) {
    if (n > 0)
        return 1;
    if (n < 0)
        return -1;
    return 0;
}

Sprite* Player::DEFAULT_SPRITE = nullptr;

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

    collider = new EntityCollider(this);

    detector = new EntityDetector(this);

    name = data.name;
    hp = data.hp;

    numenLevel = data.numen_level;
    hasUnlockedPower[Power::BODY_CONTROL] = true;
    hasUnlockedPower[Power::BODY_RESURRECTION] = data.power[Power::BODY_RESURRECTION];
    hasUnlockedPower[Power::BODY_EXPLOSION] = data.power[Power::BODY_EXPLOSION];
    hasUnlockedPower[Power::SHIELD] = data.power[Power::SHIELD];

    position = data.pos;

    walkSpeed = 6;

    interaction = Interaction::NONE;
    interactingWith = nullptr;

    if (data.controlled_entity.type == Entity::Type::NON_PLAYER_CHARACTER) {
        NPC* npc = new NPC(data.controlled_entity.name, data.controlled_entity.species, data.controlled_entity.behavior);
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

    if (data.controlled_entity.type == Entity::Type::DOLL) {
        Doll* doll = new Doll();
        doll->init();
        doll->setPosition(data.controlled_entity.pos.x, data.controlled_entity.pos.y);

        this->sprite = doll->sprite;
        this->sprite->linkTo(this);

        this->controlledEntity = doll;
        doll->controlled = true;
        this->controlled = true;

        this->walkSpeed = doll->walkSpeed;
    }

    state = data.state;
}

void Player::update() {
    Entity::update();
}

void Player::draw() {
    Entity::draw();
}

void Player::kill() {
    Entity::kill();
}

void Player::interactWith(Entity* e) {
    switch (e->type) {
    case Entity::Type::NON_PLAYER_CHARACTER:
        if (NPC* npc = dynamic_cast<NPC*>(e))
            if (npc->haveDialog)
                Game::ui->useHint(" - Talk", e);
        break;
    case Entity::Type::DEAD_BODY:
        if (haveUnlockedPower(Power::BODY_RESURRECTION))
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
        UI::AddPopUp("YOU LACK MENTAL POWER");
        return;
    }

    this->sprite = e->sprite;
    this->sprite->linkTo(this);

    this->position = e->position;

    Game::island->removeEntity(e);

    this->controlledEntity = e;
    e->controlled = true;
    this->controlled = true;

    this->walkSpeed = e->walkSpeed;
    playAnimation("Idle");
}

void Player::releaseControledEntity() {
    controlledEntity->sprite = this->sprite;
    controlledEntity->sprite->linkTo(controlledEntity);

    this->sprite = Player::DEFAULT_SPRITE;

    controlledEntity->position = this->position;
    controlledEntity->resetMovement();

    Game::island->addEntity(controlledEntity);

    controlledEntity->controlled = false;
    this->controlledEntity = nullptr;
    this->controlled = false;

    walkSpeed = 6;
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
        Game::island->addNPC(body->species, body->name, Entity::MAX_HP, body->position.x, body->position.y, body->ownerHasDialog, body->behavior);
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

Inventory* Player::parseInventory() {
    if (controlledEntity == nullptr) {
        UI::AddPopUp("YOU CANNOT OPEN YOUR INVENTORY");
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
            structure.controlled_entity = controlledEntity->getStructure();
            break;
        }
    }

    return structure;
}
