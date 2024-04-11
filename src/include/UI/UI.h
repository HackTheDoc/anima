#pragma once

#include <map>
#include <queue>
#include <string>

#include "UIElement.h"
#include "UIPopUp.h"
#include "UIHint.h"

class Portal;
class Door;
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

    void add(const std::string& tag, UIElement* element);
    void add(const std::string& tag, UIHint* element);
    void remove(const std::string& tag);

    void init();
    void update();
    void display();
    void destroy();

    void useHint(const std::string& hint);
    void useHint(const std::string& hint, Portal* p);
    void useHint(const std::string& hint, Door* p);
    void useHint(const std::string& hint, Entity* e);
    void useHint(const std::string& hint, Collider* c);
    void hideHint(const std::string& hint);

    static void AddPopUp(const std::string& text, const bool translate = true);
};