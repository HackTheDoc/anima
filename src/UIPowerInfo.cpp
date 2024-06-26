#include "include/UI/UIPowerInfo.h"

#include "include/Window.h"
#include "include/Game/Game.h"

UIPowerInfo::UIPowerInfo(const Power pid, const int w, const int h, const std::string& font) {
    this->font = font;

    rect.w = w;
    rect.h = h;

    this->pid = pid;

    std::string t, d;
    switch (pid) {
    case Power::BODY_CONTROL:
        if (Game::player->haveUnlockedPower(pid)) {
            t = "IMPERIUM";
            d = Text::Get("Allow one to take control of another's body.");
        }
        else {
            t = Text::Get("UNKNOWN");
            d = Text::Get("Pay 5 Numen tokens to unlock.");
        }
        break;
    case Power::BODY_RESURRECTION:
        if (Game::player->haveUnlockedPower(pid)) {
            t = "RESURECTIO";
            d = Text::Get("Consume 3 Numen tokens to resurrect a corpse.");
        }
        else {
            t = Text::Get("UNKNOWN");
            d = Text::Get("Pay 5 Numen tokens to unlock.");
        }
        break;
    case Power::BODY_EXPLOSION:
        /*
        if (Game::player->haveUnlockedPower(pid)) {
            t = "CREPITUS";
            d = Text::Get("Make the body you are controlling go KABOOM for 2 Numen tokens only!");
        }
        else {
            t = Text::Get("UNKNOWN");
            d = Text::Get("Pay 5 Numen tokens to unlock.");
        }
        */
        t = "UNDEFINED";
        d = "not yet implemented";
        break;
    case Power::SHIELD: // BOTTOM LEFT
        /*
        if (Game::player->haveUnlockedPower(pid)) {
            t = "SCUTUM";
            d = Text::Get("Create a shield arround yourself by consuming 5 Numen tokens.");
        }
        else {
            t = Text::Get("UNKNOWN");
            d = Text::Get("Pay 5 Numen tokens to unlock.");
        }
        */
        t = "UNDEFINED";
        d = "not yet implemented";
        break;
    default:
        t = d = "";
        break;
    }

    title = new UILabel(t, font, hue::font, rect.w);

    description = new UITextBox(d, "default", hue::font, rect.w * 2);

    place(0, 0);
}

UIPowerInfo::~UIPowerInfo() {}

void UIPowerInfo::draw() {
    Manager::DrawFilledRect(&rect, hue::text_box);

    title->draw();

    Manager::DrawRect(&rect, hue::border);

    SDL_Point m;
    SDL_GetMouseState(&m.x, &m.y);

    if (!SDL_PointInRect(&m, &rect)) return;

    description->place(m.x, m.y);
    description->draw();
}

void UIPowerInfo::update() {
    if (Game::player->haveUnlockedPower(pid)) return;

    SDL_Point m;
    SDL_GetMouseState(&m.x, &m.y);

    if (!SDL_PointInRect(&m, &rect) || !Window::event.mouseClickLeft()) return;

    if (Game::player->numenLevel < 5) {
        UI::AddPopUp("YOU LACK NUMEN TOKENS");
        return;
    }

    /// TODO: remove when implemented
    if (pid == Power::BODY_EXPLOSION || pid == Power::SHIELD) {
        UI::AddPopUp("NOT YET IMPLEMENTED", false);
        return;
    }

    Game::player->unlockPower(pid);

    switch (pid) {
    case Power::BODY_CONTROL:
        title->setText("IMPERIUM", font, hue::font, rect.w);
        description->setText(Text::Get("Allow one to take control of another's body."), font, hue::font, rect.w * 2);
        break;
    case Power::BODY_RESURRECTION:
        title->setText("RESURECTIO", font, hue::font, rect.w);
        description->setText(Text::Get("Consume 3 Numen tokens to resurrect a corpse."), font, hue::font, rect.w * 2);
        break;
    case Power::BODY_EXPLOSION:
        title->setText("CREPITUS", font, hue::font, rect.w);
        description->setText(Text::Get("Make the body you are controlling go KABOOM for 2 Numen tokens only!"), font, hue::font, rect.w * 2);
        break;
    case Power::SHIELD:
        title->setText("SCUTUM", font, hue::font, rect.w);
        description->setText(Text::Get("Create a shield arround yourself by consuming 5 Numen tokens."), font, hue::font, rect.w * 2);
        break;
    default:
        break;
    }

    place(rect.x, rect.y);
}

void UIPowerInfo::destroy() {
    title->destroy();
    description->destroy();
}

void UIPowerInfo::place(const int x, const int y) {
    rect.x = x;
    rect.y = y;

    title->place(
        x + (rect.w - title->width()) / 2,
        y + (rect.h - title->height()) / 2 + 4 * (Window::fullscreen + 1)
    );
}
