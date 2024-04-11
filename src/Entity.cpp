#include "include/Game/Entities/Entity.h"

#include "include/Window.h" //uselesss if not in dev mode

#include "include/Game/Game.h"
#include "include/Game/Map/Tile.h"
#include "include/Game/Components/Collision.h"

const int Entity::MAX_HP = 3;

Entity::Entity() {
    name = "unknown";

    type = Type::UNKNOWN;
    species = Species::HUMAN;
    behavior = Behavior::STATIC;

    hp = MAX_HP;
    numenLevel = INT8_MAX;

    inventory.capacity = 0;
}

Entity::~Entity() {}

void Entity::init() {
    immortal = false;
    controlled = false;

    sprite = nullptr;
    collider = nullptr;
    detector = nullptr;

    position.Zero();
    velocity.Zero();

    switch (species) {
    case Species::FAIRIES:
        width = 64;
        height = 64;
        walkSpeed = 8;
        break;
    case Species::GOBLIN:
        width = 128;
        height = 128;
        walkSpeed = 2;
        break;
    case Species::HUMAN:
    default:
        width = 128;
        height = 128;
        walkSpeed = 4;
        break;
    }

}

void Entity::update() {
    if (sprite)
        sprite->update();
    if (collider)
        collider->update();
    if (detector)
        detector->update();

    position.x += velocity.x * walkSpeed;
    position.y += velocity.y * walkSpeed;
}

void Entity::draw() {
    if (sprite)
        sprite->draw();
#ifdef DEV_MOD
    if (collider)
        collider->draw();
    if (detector)
        detector->draw();
#endif
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

void Entity::playAnimation(const std::string& animationName) {
    sprite->play(animationName);
}

void Entity::setPosition(const int x, const int y) {
    position.x = x;
    position.y = y;
}

void Entity::setPosition(const Vector2D& pos) {
    setPosition(pos.x, pos.y);
}

void Entity::setFlip(const SDL_RendererFlip flipMod) {
    sprite->spriteFlip = flipMod;
}

void Entity::resetMovement() {
    velocity.Zero();
}

void Entity::reverseMovement() {
    position.x -= 2 * velocity.x * walkSpeed;
    position.y -= 2 * velocity.y * walkSpeed;
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

    Item* i = Item::Create(id);

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

bool Entity::has_died() {
    return hp == 0;
}

/// @TODO: deceide the value for each species...
int Entity::GetMentalPower(Entity::Species species) {
    switch (species) {
    case Species::HUMAN:
    case Species::FAIRIES:
        return 1;
    case Species::GOBLIN:
        return 2;
    default:
        return INT8_MAX;
    }
}

void Entity::randomMovement() {
    Tile* t = Game::island->map->getTileAt(position);

    if (!t->walkable && Collision::AABB(collider->rect, t->collider)) {
        reverseMovement();
        resetMovement();
        return;
    }

    if (!velocity.isZero() && rand() % 20 != 0) return;

    const Vector2D dir[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

    int i = rand() % 4;
    velocity = dir[i];

    if (velocity.isZero()) return;

    playAnimation("Walk");

    if (velocity.x > 0) setFlip(SDL_FLIP_NONE);
    else setFlip(SDL_FLIP_HORIZONTAL);
}
