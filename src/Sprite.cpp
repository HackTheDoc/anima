#include "include/Game/Components/Sprite.h"

#include "include/Manager.h"
#include "include/Game/Game.h"

Sprite::Sprite(Entity* o) {
    linkTo(o);
    texture = nullptr;
    srcRect = destRect = {0,0,0,0};
    frames = animationSpeed = animationIndex = 0;
}

Sprite::~Sprite() {}

void Sprite::init(std::string tag, int numberOfAnimations) {
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = owner->width / 4;
    srcRect.h = owner->height / 4;

    destRect.w = owner->width;
    destRect.h = owner->height;

    setSprite(tag);

    spriteFlip = SDL_FLIP_NONE;

    if (numberOfAnimations < 0) {
        animated = false;
        return;
    }

    animated = true;
    Animation animation;
    for (int i = 0; i < numberOfAnimations; i++) {
        switch (i) {
        case 0:
            animation = Animation(0, 4, 160);
            animations.emplace("Spawn", animation);
            break;
        case 1:
            animation = Animation(1, 4, 160);
            animations.emplace("Idle", animation);
            break;
        case 2:
            animation = Animation(2, 8, 100);
            animations.emplace("Walk", animation);
            break;
        case 3:
            animation = Animation(6, 8, 100);
            animations.emplace("Roll", animation);
            break;
        case 4:
            animation = Animation(8, 4, 160);
            animations.emplace("Hit", animation);
            break;
        case 5:
            animation = Animation(9, 4, 160);
            animations.emplace("Death", animation);
            break;
        case 6:
            animation = Animation(3, 1, 720);
            animations.emplace("Jump - Idle", animation);
            break;
        case 7:
            animation = Animation(4, 1, 720);
            animations.emplace("Jump - Run", animation);
            break;
        case 8:
            animation = Animation(5, 3, 240);
            animations.emplace("Land", animation);
            break;
        case 9:
            animation = Animation(7, 4, 160);
            animations.emplace("Turn", animation);
            break;
        default:
            break;
        }
    }

    play("Idle");
}

void Sprite::init(int species, int numberOfAnimations) {
    std::string tag;

    switch (species)
    {
    case Entity::Species::GOBLIN:
        tag = "goblin";
        break;
    case Entity::Species::HUMAN:
    default:
        tag = "human";
        break;
    }

    init(tag, numberOfAnimations);
}

void Sprite::update() {
    if (animated) {
        int currentFrame = (int)((SDL_GetTicks64() / animationSpeed) % frames);
        srcRect.x = srcRect.w * currentFrame;
        srcRect.y = animationIndex * srcRect.h;
    }

    destRect.x = owner->position.x - (destRect.w - owner->width / 4) / 2 - Game::camera.x;
    destRect.y = owner->position.y - (destRect.h - owner->height / 2) * 0.75 - Game::camera.y;
}

void Sprite::draw() {
    Manager::Draw(texture, &srcRect, &destRect, spriteFlip);
}

void Sprite::destroy() {
    texture = nullptr;
}

void Sprite::setSprite(std::string tag) {
    texture = Window::manager->getTexture(tag);
}

void Sprite::play(std::string animationName) {
    if (!animated) return;
    
    currentAnimation = animationName;
    frames = animations[animationName].frames;
    animationIndex = animations[animationName].index;
    animationSpeed = animations[animationName].speed;
}

void Sprite::linkTo(Entity* o) {
    owner = o;
}

void Sprite::useFrame(int y, int x) {
    srcRect.x = srcRect.w * x;
    srcRect.y = srcRect.h * y;
}
