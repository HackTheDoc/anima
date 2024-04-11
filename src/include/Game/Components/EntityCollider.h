#pragma once

#include "Collider.h"

class Entity;

class EntityCollider : public Collider {
public:
    EntityCollider(Entity* o = nullptr);
    ~EntityCollider();

    void update();

    void setOwner(Entity* o);

private:
    Entity* owner;
};
