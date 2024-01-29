#include "include/Game/Entities/Entity.h"

#include "include/Game/Game.h"
#include "include/Game/Map/Tile.h"

const int Entity::MAX_HP = 3;

Entity::Entity() {
    name = "unknown";
    type = Type::UNKNOWN;
    species = Entity::Species::HUMAN;
    inventory.capacity = 0;
    numenLevel = INT8_MAX;
}

Entity::~Entity() {}

void Entity::init() {
    immortal = false;

    sprite = nullptr;
    collider = nullptr;
    detector = nullptr;

    hp = 1;

    position.Zero();

    width = 128;
    height = 128;

    hSpeed = 0;
    vSpeed = 0;

    walkSpeed = 2;

    controlled = false;
}

void Entity::update() {
    if (sprite)
        sprite->update();
    if (collider)
        collider->update();
    if (detector)
        detector->update();

    position.x += hSpeed*walkSpeed;
    position.y += vSpeed*walkSpeed;
}

void Entity::draw() {
    if (sprite)
        sprite->draw();
    if (collider)
        collider->draw();
    if (detector)
        detector->draw();
}

void Entity::kill() {
    if (sprite) {
        sprite->destroy();
        delete sprite;
        sprite = nullptr;
    }
    if (collider) {
        delete collider;
        collider = nullptr;
    }
    if (detector) {
        delete detector;
        detector = nullptr;
    }
}

void Entity::playAnimation(std::string animationName) {
    sprite->play(animationName);
}

void Entity::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void Entity::setPosition(Vector2D pos) {
    setPosition(pos.x, pos.y);
}

void Entity::setFlip(SDL_RendererFlip flipMod) {
    sprite->spriteFlip = flipMod;
}

void Entity::resetMovement() {
    hSpeed = vSpeed = 0;
}

void Entity::reverseMovement() {
    position.x -= 2*hSpeed*walkSpeed;
    position.y -= 2*vSpeed*walkSpeed;
}

void Entity::startInteraction() {
    Game::player->resetMovement();
    Game::player->state = Player::State::IN_DIALOG;
}

void Entity::closeIntereaction() {
    Game::player->interaction = Interaction::NONE;
    Game::player->interactingWith = nullptr;
    Game::player->state = Player::State::FREE;
}

void Entity::addItemToInventory(Item::ID id) {
    if (inventory.item.size() >= inventory.capacity)
        return;

    Item *i = Item::Create(id);

    if (i == nullptr)
        return;

    inventory.item.push_back(i);
}

bool Entity::addItemToInventory(Item* item) {
    if (inventory.item.size() >= inventory.capacity)
        return false;

    if (item == nullptr)
        return false;

    inventory.item.push_back(item);

    return true;
}

EntityStructure Entity::getStructure() {
    return {type, Entity::Type::UNKNOWN, species, name, hp, position, inventory, false};
}

/// @TODO: deceide the value for each species...
int Entity::GetMentalPower(Entity::Species species) {
    switch (species) {
    case Species::HUMAN:
        return 1;
    case Species::GOBLIN:
        return 2;
    default:
        return INT8_MAX;
    }
}
