#pragma once

#include <map>
#include <queue>
#include <string>

#include "UIElement.h"
#include "UIPopUp.h"

class UIHint;

class Portal;
class Entity;
class Collider;

class UI {
private:
    static std::priority_queue<UIPopUp*> popups_queue;

    std::map<std::string, UIElement*> elements;
    std::map<std::string, UIHint*> hints;
    std::string currentHint;

public:
    UI();
    ~UI();

    void add(std::string tag, UIElement* element);
    void add(std::string tag, UIHint* element);
    void remove(std::string tag);

    void init();
    void update();
    void display();
    void destroy();

    void useHint(std::string hint);
    void useHint(std::string hint, Portal* p);
    void useHint(std::string hint, Entity* e);
    void useHint(std::string hint, Collider* c);
    void hideHint(std::string hint);

    static void AddPopUp(const std::string& text);
};