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
    Struct::Player data = Save::LoadPlayer();
    
    Entity::init();

    DEFAULT_SPRITE = new Sprite(this);
    DEFAULT_SPRITE->init("spirit", 6);
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

    // tutorial
    Tutorial::Init(data.tutorial_step);

    // state & quests
    state = data.state;

    quest = new QuestSystem(data.curr_main_quest);
    for (const Quest::ID q : data.curr_other_quests)
        quest->addQuest(q);

    // pos & speed
    position = data.pos;
    walkSpeed = 6;

    // interactions
    interaction = Interaction::NONE;
    interactingWith = nullptr;

    if (data.is_controlling_an_entity) {
        struct Visitor {
            Player* player;

            void operator()(const Struct::NPC& data) const {
                NPC* npc = new NPC(data.name, data.species, data.behavior, data.inventory);
                npc->init();
                npc->setPosition(data.pos.x, data.pos.y);
                npc->haveDialog = data.hasdialog;
                npc->hp = data.hp;

                player->sprite = npc->sprite;
                player->sprite->linkTo(player);

                player->setControlledEntity(npc);
                npc->controlled = true;
                player->controlled = true;

                player->walkSpeed = npc->walkSpeed;
            }

            void operator()(const Struct::Doll& data) const {
                Doll* doll = new Doll(data.inventory);
                doll->init();
                doll->setPosition(data.pos.x, data.pos.y);

                player->sprite = doll->sprite;
                player->sprite->linkTo(player);

                player->setControlledEntity(doll);
                doll->controlled = true;
                player->controlled = true;

                player->walkSpeed = doll->walkSpeed;
            }

            void operator()(const Struct::DeadBody& data) const {}
        };

        Visitor visitor{ this };
        std::visit(visitor, data.controlled_entity.e);
    }
    else controlledEntity = nullptr;

    setHealthDecreasalRate();

    Game::LoadIsland(data.curr_island_on);
}

void Player::update() {
    Entity::update();

    if (controlledEntity == nullptr) {
        timeLeftBeforeHealthDecreasalOfControlledEntity--;
        std::cout << timeLeftBeforeHealthDecreasalOfControlledEntity << std::endl;
        if (timeLeftBeforeHealthDecreasalOfControlledEntity > 0)
            return;
        hp = 0;
        return;
    }

    if (controlledEntity->immortal)
        return;

    timeLeftBeforeHealthDecreasalOfControlledEntity--;

    if (timeLeftBeforeHealthDecreasalOfControlledEntity > 0)
        return;

    controlledEntity->hp--;
    setHealthDecreasalRate();

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
            position,
            controlledEntity->inventory,
            controlledEntity->type,
            controlledEntity->name,
            hasdialog,
            controlledEntity->behavior
        );

        controlledEntity->kill();
        reset();
    }
}

void Player::draw() {
    Entity::draw();
}

void Player::kill() {
    Tutorial::Destroy();

    if (controlledEntity != nullptr)
        controlledEntity->kill();
    controlledEntity = nullptr;

    DEFAULT_SPRITE->destroy();
    delete DEFAULT_SPRITE;
    DEFAULT_SPRITE = nullptr;

    delete DEFAULT_COLLIDER;
    DEFAULT_COLLIDER = nullptr;

    delete DEFAULT_DETECTOR;
    DEFAULT_DETECTOR = nullptr;

    delete quest;
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
        if (DeadBody* body = dynamic_cast<DeadBody*>(e))
            searchDeadBody(body);
        break;
    case Interaction::TAKE_CONTROL:
        takeControlOf(e);
        break;
    case Interaction::RESURRECT:
        if (DeadBody* body = dynamic_cast<DeadBody*>(e))
            resurrectDeadBody(body);
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

void Player::searchDeadBody(DeadBody* body) {
    if (!controlled) return;

    Inventory* inv = parseInventory();

    if (inv->is_full())
        UI::AddPopUp("INVENTORY FULL");
    else if (body->inventory.is_empty())
        UI::AddPopUp("NOTHING WAS FOUND");
    else {
        UI::AddPopUp("YOU FOUND SOMETHING");
        Item* i = body->inventory.extract_random_item();
        inv->add_item(i);
    }
}

void Player::resurrectDeadBody(DeadBody* body) {
    if (body->numenLevel > this->numenLevel) {
        UI::AddPopUp("YOU LACK MENTAL POWER");
        return;
    }

    Game::ui->useHint("NONE");

    Game::island->removeEntity(body);

    switch (body->ownerType) {
    case Entity::Type::NON_PLAYER_CHARACTER:
        Game::island->addNPC(
            body->position,
            body->species,
            body->behavior,
            body->name,
            Entity::MAX_HP,
            body->ownerHasDialog, 
            body->inventory
        );
        break;
    default:
        break;
    }

    modifyNumenLevelBy(-3);
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

    this->hp = e->hp;
    setHealthDecreasalRate();

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

void Player::setControlledEntity(Entity* e) {
    controlledEntity = e;
}

Entity* Player::parseControlledEntity() {
    return controlledEntity;
}

Struct::Player Player::getStructure() {
    Struct::Player structure;

    structure.name = name;
    structure.hp = hp;
    structure.numen_level = numenLevel;
    structure.power[Power::BODY_RESURRECTION] = hasUnlockedPower[Power::BODY_RESURRECTION];
    structure.power[Power::BODY_EXPLOSION] = hasUnlockedPower[Power::BODY_EXPLOSION];
    structure.power[Power::SHIELD] = hasUnlockedPower[Power::SHIELD];


    if (state == State::IN_DIALOG)
        structure.state = State::FREE;
    else structure.state = state;

    structure.tutorial_step = Tutorial::current;

    structure.curr_island_on = Game::island->getName();
    structure.pos = position;

    structure.curr_main_quest = quest->main.id;
    for (Quest q : quest->others)
        structure.curr_other_quests.push_back(q.id);

    structure.is_controlling_an_entity = false;
    if (controlledEntity != nullptr) {
        structure.is_controlling_an_entity = true;
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
            break;
        }
    }

    return structure;
}

/// TODO: define the health decreasal rate for each species
void Player::setHealthDecreasalRate() {
    // SPIRIT FORM OF THE PLAYER
    if (controlledEntity == nullptr) {
        std::cout << "aa" << std::endl;
        timeLeftBeforeHealthDecreasalOfControlledEntity = 900 * std::max(1, numenLevel / 2);
        return;
    }

    // CONTROLLING AN ENTITY
    switch (controlledEntity->species) {
    case Entity::Species::FAIRIES:
        timeLeftBeforeHealthDecreasalOfControlledEntity = 180;
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

    hp = 1;
    setHealthDecreasalRate();
}
