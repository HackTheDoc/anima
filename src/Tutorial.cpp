#include "include/Game/Tutorial.h"

#include "include/Manager.h"
#include "include/Window.h"
#include "include/KeyMap.h"

Tutorial::Step Tutorial::current = Tutorial::Step::NONE;
bool Tutorial::activated = true;
SDL_Rect Tutorial::container{
    4 * Window::screen.w / 5 - 8 * (Window::fullscreen + 1),
    8 * (Window::fullscreen + 1),
    Window::screen.w / 5,
    0
};
UILabel* Tutorial::content = nullptr;

void Tutorial::Load(const int id) {
    current = (Step)id;

    const int span = 4 * (Window::fullscreen + 1);
    const std::string& press = Text::Get("Press ");

    switch (id) {
    case Step::OPEN_INVENTORY:
        content->setText(
            press + to_string(Event::ID::OPEN_INVENTORY) + Text::Get(" to open inventory."),
            "default",
            hue::white,
            container.w - 2 * span
        );
        break;
    case Step::OPEN_QUESTS:
        content->setText(
            press + to_string(Event::ID::OPEN_QUEST_MENU) + Text::Get(" to open quests."),
            "default",
            hue::white,
            container.w - 2 * span
        );
        break;
    case Step::OPEN_BENEDICTIONS:
        content->setText(
            press + to_string(Event::ID::OPEN_POWER_MENU) + Text::Get(" to open benedictions."),
            "default",
            hue::white,
            container.w - 2 * span
        );
        break;
    case Step::USE_CONTROL_POWER:
        content->setText(
            press + to_string(Event::ID::BODY_CONTROL) + Text::Get(" to release or take control of a body."),
            "default",
            hue::white,
            container.w - 2 * span
        );
        break;
    case Step::MOVEMENTS:
        content->setText(
            press + to_string(Event::ID::MOVE_UP) + "," + to_string(Event::ID::MOVE_DOWN) + "," + to_string(Event::ID::MOVE_LEFT) + "," + to_string(Event::ID::MOVE_RIGHT) + Text::Get(" to move."),
            "default",
            hue::white,
            container.w - 2 * span
        );
        break;
    case Step::FINISHED:
        content->setText(
            "finished",
            "default",
            hue::white,
            container.w - 2 * span
        );
        break;
    default:
        break;
    }

    container.h = content->height() + 2 * span;
    content->place(span, span);
};

void Tutorial::Init(const int id) {
    if (content) Destroy();

    content = new UILabel();
    Load(id);
}

void Tutorial::Render() {
    if (!activated || current == Step::NONE || current == Step::FINISHED) return;

    Manager::DrawFilledRect(&container, hue::blur_dark);
    Manager::SetViewport(&container);

    content->draw();

    Manager::SetViewport(nullptr);
    Manager::DrawRect(&container, hue::white);
}

void Tutorial::Destroy() {
    content->destroy();
    content = nullptr;
}

void Tutorial::Complete(const Step id) {
    if (id != current) return;

    switch (id) {
    case Step::OPEN_INVENTORY:
    case Step::OPEN_QUESTS:
    case Step::OPEN_BENEDICTIONS:
    case Step::USE_CONTROL_POWER:
    case Step::MOVEMENTS:
        Load(id + 1);
        break;
    case Step::NONE:
    case Step::FINISHED:
    default:
        Load(Step::NONE);
        break;
    }
}
