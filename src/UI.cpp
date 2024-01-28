#include "include/UI/UI.h"

#include "include/Game/Game.h"
#include "include/UI/UIHint.h"
#include "include/UI/UIPopUp.h"

#include "include/KeyMap.h"

UI::UI() {}

UI::~UI() {
    elements.clear();
}

void UI::add(std::string tag, UIElement* element) {
    elements.emplace(tag, element);
}

void UI::add(std::string tag, UIHint* element) {
    hints.emplace(tag, element);
}

void UI::add(std::string tag, UIPopUp* element) {
    popups.emplace(tag, element);
    popups_queue.push(element);
}

void UI::remove(std::string tag) {
    elements.erase(tag);
}

void UI::init() {
    destroy();

    /*
    UIHealthBar* healthBar = new UIHealthBar();
    healthBar->place(8, 8);
    add("healthBar", healthBar);
    */

    currentHint = "NONE";

    UIHint* activate = new UIHint(to_string(Event::ID::INTERACT) + Text::Get(" - Activate"), "small");
    add(" - Activate", activate);

    UIHint* talk = new UIHint(to_string(Event::ID::INTERACT) + Text::Get(" - Talk"), "default");
    add(" - Talk", talk);

    UIHint* resurrect = new UIHint(to_string(Event::ID::BODY_RESURRECTION) + Text::Get(" - Resurrect"), "default");
    add(" - Resurrect", resurrect);

    UIHint* pickUp = new UIHint(to_string(Event::ID::INTERACT) + Text::Get(" - Pick up"), "default");
    add(" - Pick up", pickUp);

    /* ----- POPUPS ----- */
    UIPopUp *nw = new UIPopUp();
    nw->addLabel("YOU LACK NUMEN TOKENS");
    add("YOU LACK NUMEN TOKENS", nw);

    UIPopUp *iw = new UIPopUp();
    iw->addLabel("YOU CANNOT OPEN YOUR INVENTORY");
    add("YOU CANNOT OPEN YOUR INVENTORY", iw);

    UIPopUp *piw = new UIPopUp();
    piw->addLabel("YOU CANNOT PICK UP ITEMS IN YOUR CURRENT STATE");
    add("YOU CANNOT PICK UP ITEMS IN YOUR CURRENT STATE", piw);

    UIPopUp *ifw = new UIPopUp();
    ifw->addLabel("INVENTORY FULL");
    add("INVENTORY FULL", ifw);
}

void UI::update() {
    for (auto e : elements)
        e.second->update();
}

void UI::display() {
    for (auto e : elements)
        e.second->draw();

    int offset = 0;
    std::queue<UIPopUp*> temp;
    while (!popups_queue.empty()) {
        UIPopUp* p = popups_queue.top();
        popups_queue.pop();
        if (p->timeLeft > 0) {
            p->draw(offset);
            offset += p->height() + UIElement::MARGIN*(1+Window::fullscreen);
        }
        temp.push(p);
    }
    while (!temp.empty()) {
        popups_queue.push(temp.front());
        temp.pop();
    }

    if (currentHint != "NONE")
        hints[currentHint]->draw();
}

void UI::destroy() {
    for (auto e : elements)
        e.second->destroy();
    elements.clear();

    for (auto s : hints)
        s.second->destroy();
    hints.clear();

    while (!popups_queue.empty())
        popups_queue.pop();
    for (auto p : popups)
        p.second->destroy();
    popups.clear();
}

void UI::useHint(std::string hint) {
    currentHint = hint;
}

void UI::useHint(std::string hint, Portal* p) {
    currentHint = hint;
    if (currentHint != "NONE")
        hints[currentHint]->place(p);
}

void UI::useHint(std::string hint, Entity* e) {
    currentHint = hint;
    if (currentHint != "NONE")
        hints[currentHint]->place(e);
}

void UI::useHint(std::string hint, Collider* c) {
    currentHint = hint;
    if (currentHint != "NONE")
        hints[currentHint]->place(c);
}

void UI::hideHint(std::string hint) {
    if (currentHint != hint)
        return;
    currentHint = "NONE";
}

void UI::usePopUp(const std::string& text) {
    popups[text]->timeLeft = UIPopUp::DELAY;
}
