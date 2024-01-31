#include "include/UI/UIKeyInput.h"

#include "include/Window.h"
#include "include/Manager.h"
#include "include/KeyMap.h"

int UIKeyInput::Height = 0;

UIKeyInput::UIKeyInput(Event::ID eid) {
    this->eid = eid;

    rect = {0, 0, Window::screen.w / 4 + 64 * (Window::fullscreen + 1), UIKeyInput::Height};

    setTitle();
    setKey();
}

UIKeyInput::~UIKeyInput() {}

void UIKeyInput::draw() {
    Manager::Draw(title, nullptr, &titleRect);
    Manager::Draw(key, nullptr, &keyRect);

    Manager::DrawLine(
        rect.x + 2 * rect.w / 3,
        rect.y,
        rect.x + 2 * rect.w / 3,
        rect.y + rect.h,
        hue::white);
    Manager::DrawRect(&rect, hue::white);
}

void UIKeyInput::update() {
    SDL_Point m;
    SDL_GetMouseState(&m.x, &m.y);

    if (Window::event.mouseClickLeft())
    {
        if (SDL_PointInRect(&m, &rect))
        {
            actived = true;
            key = Manager::GenerateText(
                "...",
                Window::manager->getFont("default"),
                hue::white);
            SDL_QueryTexture(key, NULL, NULL, &keyRect.w, &keyRect.h);
            place(rect.x, rect.y);
        }
        else
        {
            actived = false;
            setKey();
        }
    }

    if (actived && Window::event.e.type == SDL_KEYUP)
    {
        SDL_KeyCode kcode = SDL_KeyCode(Window::event.e.key.keysym.sym);

        bool success = KeyMap::Set(eid, kcode);

        if (success)
        {
            this->eid = KeyMap::Key[kcode];

            actived = false;

            setKey();
        }
    }
}

void UIKeyInput::destroy() {
    SDL_DestroyTexture(title);
    title = nullptr;

    SDL_DestroyTexture(key);
    key = nullptr;
}

void UIKeyInput::reload() {
    rect = {0, 0, Window::screen.w / 4 + 64 * (Window::fullscreen + 1), UIKeyInput::Height};

    destroy();
    setTitle();
    setKey();
}

void UIKeyInput::place(int x, int y) {
    rect.x = x;
    rect.y = y;

    titleRect.x = x + (2 * rect.w / 3 - titleRect.w) / 2;
    titleRect.y = y + (rect.h - titleRect.h) / 2 + 8 * (Window::fullscreen + 1);

    keyRect.x = x + 2 * rect.w / 3 + (rect.w / 3 - keyRect.w) / 2;
    keyRect.y = y + (rect.h - keyRect.h) / 2 + 8 * (Window::fullscreen + 1);
}

void UIKeyInput::setTitle() {
    std::string t;

    switch (eid)
    {
    case Event::ID::PAUSE:
        t = Text::Get("Pause");
        break;
    case Event::ID::OPEN_POWER_MENU:
        t = Text::Get("Benedictions");
        break;
    case Event::ID::OPEN_INVENTORY:
        t = Text::Get("Inventory");
        break;
    case Event::ID::MOVE_UP:
        t = Text::Get("Move Up");
        break;
    case Event::ID::MOVE_DOWN:
        t = Text::Get("Move Down");
        break;
    case Event::ID::MOVE_LEFT:
        t = Text::Get("Move Left");
        break;
    case Event::ID::MOVE_RIGHT:
        t = Text::Get("Move Right");
        break;
    case Event::ID::INTERACT:
        t = Text::Get("Interact");
        break;
    case Event::ID::BODY_CONTROL:
        t = Text::Get("Take Control");
        break;
    case Event::ID::BODY_RESURRECTION:
        t = Text::Get("Resurrect");
        break;
    case Event::ID::VALID_DIALOG:
        t = Text::Get("Valid");
        break;
    case Event::ID::NEXT_ANSWER:
        t = Text::Get("Next Answer");
        break;
    case Event::ID::PREVIOUS_ANSWER:
        t = Text::Get("Prev. Answer");
        break;
    case Event::ID::UNKNOWN:
    default:
        t = "UNKNOWN";
        break;
    }

    title = Manager::GenerateText(
        t.c_str(),
        Window::manager->getFont("default"),
        hue::white,
        2 * rect.w / 3
    );
    SDL_QueryTexture(title, NULL, NULL, &titleRect.w, &titleRect.h);
}

void UIKeyInput::setKey() {
    std::string t = to_string(eid);
    if (t == "")
        t = "...";

    key = Manager::GenerateText(
        t.c_str(),
        Window::manager->getFont("default"),
        hue::white,
        rect.w / 3
    );
    SDL_QueryTexture(key, NULL, NULL, &keyRect.w, &keyRect.h);
    place(rect.x, rect.y);

    if (t == "...")
        actived = true;
}
