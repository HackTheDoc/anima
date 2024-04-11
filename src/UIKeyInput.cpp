#include "include/UI/UIKeyInput.h"

#include "include/Window.h"
#include "include/KeyMap.h"

int UIKeyInput::Height = 0;

UIKeyInput::UIKeyInput(const Event::ID eid) {
    this->eid = eid;

    rect = { 0, 0, Window::screen.w / 4 + 64 * (Window::fullscreen + 1), UIKeyInput::Height };

    lbl_title = new UILabel();
    setTitle();

    lbl_key = new UILabel();
    setKey();
}

UIKeyInput::~UIKeyInput() {}

void UIKeyInput::draw() {
    lbl_title->draw();
    lbl_key->draw();

    Manager::DrawLine(
        rect.x + 2 * rect.w / 3,
        rect.y,
        rect.x + 2 * rect.w / 3,
        rect.y + rect.h,
        hue::border);
    Manager::DrawRect(&rect, hue::border);
}

void UIKeyInput::update() {
    SDL_Point m;
    SDL_GetMouseState(&m.x, &m.y);

    if (Window::event.mouseClickLeft()) {
        if (SDL_PointInRect(&m, &rect)) {
            actived = true;
            lbl_key->setText("...", "default", hue::font);
            place(rect.x, rect.y);
        }
        else {
            actived = false;
            setKey();
        }
    }

    if (actived && Window::event.e.type == SDL_KEYUP) {
        SDL_KeyCode kcode = SDL_KeyCode(Window::event.e.key.keysym.sym);

        bool success = KeyMap::Set(eid, kcode);

        if (success) {
            this->eid = KeyMap::Key[kcode];
            actived = false;
            setKey();
        }
    }
}

void UIKeyInput::destroy() {
    lbl_title->destroy();
    lbl_key->destroy();
}

void UIKeyInput::reload() {
    rect = { 0, 0, Window::screen.w / 4 + 64 * (Window::fullscreen + 1), UIKeyInput::Height };

    destroy();
    setTitle();
    setKey();
}

void UIKeyInput::place(int x, int y) {
    rect.x = x;
    rect.y = y;

    lbl_title->place(
        x + (2 * rect.w / 3 - lbl_title->width()) / 2,
        y + (rect.h - lbl_title->height()) / 2 + 8 * (Window::fullscreen + 1)
    );

    lbl_key->place(
        x + 2 * rect.w / 3 + (rect.w / 3 - lbl_key->width()) / 2,
        y + (rect.h - lbl_key->height()) / 2 + 8 * (Window::fullscreen + 1)
    );
}

void UIKeyInput::setTitle() {
    std::string t;

    switch (eid) {
    case Event::ID::PAUSE:
        t = Text::Get("Pause");
        break;
    case Event::ID::OPEN_POWER_MENU:
        t = Text::Get("Benedictions");
        break;
    case Event::ID::OPEN_INVENTORY:
        t = Text::Get("Inventory");
        break;
    case Event::ID::OPEN_QUEST_MENU:
        t = Text::Get("Quests");
        break;
    case Event::ID::OPEN_IDENTITY_MENU:
        t = Text::Get("Identity");
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

    lbl_title->setText(t, "default", hue::font, 2 * rect.w / 3);
}

void UIKeyInput::setKey() {
    std::string t = to_string(eid);
    if (t == "") t = "...";

    lbl_key->setText(t, "default", hue::font, rect.w / 3);
    place(rect.x, rect.y);

    if (t == "...") actived = true;
}
