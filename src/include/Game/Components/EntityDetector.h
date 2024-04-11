#pragma once

#include "Collider.h"

class Entity;

class EntityDetector : public Collider {
public:
    EntityDetector(Entity* o = nullptr);
    ~EntityDetector();

    void update();
    void draw();
    void setOwner(Entity* o);

private:
    Entity* owner;
};
