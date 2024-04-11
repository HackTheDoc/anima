#include "include/WindowStates/OptionsMenu.h"

#include "include/Window.h"
#include "include/Save.h"
#include "include/Game/Tutorial.h"

#include "include/UI/UIElements.h"

OptionsMenu::OptionsMenu() {}

OptionsMenu::~OptionsMenu() {}

void OptionsMenu::createGeneralPage() {
    UIWindowModeSelector* wms = new UIWindowModeSelector();
    wms->place(
        (Window::screen.w - wms->width()) / 2,
        border.y + 32 * (Window::fullscreen + 1)
    );

    UILanguageSelector* lgs = new UILanguageSelector();
    lgs->place(
        (Window::screen.w - lgs->width()) / 2,
        wms->y() + wms->height() + 32 * (Window::fullscreen + 1)
    );

    UIActivator* sma = new UIActivator("Save Mode:", &Save::Auto);
    sma->place(
        (Window::screen.w - sma->width()) / 2,
        lgs->y() + lgs->height() + 32 * (Window::fullscreen + 1)
    );

    UIActivator* tma = new UIActivator("Tutorial:", &Tutorial::activated);
    tma->place(
        (Window::screen.w - tma->width()) / 2,
        sma->y() + sma->height() + 32 * (Window::fullscreen + 1)
    );

    page["general"] = {
        {"wms", wms},
        {"lgs", lgs},
        {"sma", sma},
        {"tma", tma}
    };
}

void OptionsMenu::reloadGeneralPage() {
    UIWindowModeSelector* wms = static_cast<UIWindowModeSelector*>(page["general"]["wms"]);
    wms->reload();
    wms->place(
        (Window::screen.w - wms->width()) / 2,
        border.y + 32 * (Window::fullscreen + 1)
    );

    UILanguageSelector* lgs = static_cast<UILanguageSelector*>(page["general"]["lgs"]);
    lgs->reload();
    lgs->place(
        (Window::screen.w - lgs->width()) / 2,
        wms->y() + wms->height() + 32 * (Window::fullscreen + 1)
    );

    UIActivator* sma = static_cast<UIActivator*>(page["general"]["sma"]);
    sma->reload();
    sma->place(
        (Window::screen.w - sma->width()) / 2,
        lgs->y() + lgs->height() + 32 * (Window::fullscreen + 1)
    );

    UIActivator* tma = static_cast<UIActivator*>(page["general"]["tma"]);
    tma->reload();
    tma->place(
        (Window::screen.w - tma->width()) / 2,
        sma->y() + sma->height() + 32 * (Window::fullscreen + 1)
    );
}

void OptionsMenu::createControlsPage() {
    UIKeyInput::Height = (Window::screen.h - border.y - border.h) / 10;

    const int w = Window::screen.w / 3;
    const int y = border.y + border.h;

    /*  ----- IDK ----- */

    UIKeyInput* kp = new UIKeyInput(Event::ID::PAUSE);
    kp->place(
        (w - kp->width()) / 2,
        y + UIKeyInput::Height / 2
    );

    UIKeyInput* kpm = new UIKeyInput(Event::ID::OPEN_POWER_MENU);
    kpm->place(
        (w - kp->width()) / 2,
        y + 3 * UIKeyInput::Height / 2
    );

    UIKeyInput* kim = new UIKeyInput(Event::ID::OPEN_INVENTORY);
    kim->place(
        (w - kp->width()) / 2,
        y + 5 * UIKeyInput::Height / 2
    );

    UIKeyInput* kqm = new UIKeyInput(Event::ID::OPEN_QUEST_MENU);
    kqm->place(
        (w - kp->width()) / 2,
        y + 7 * UIKeyInput::Height / 2
    );

    UIKeyInput* kidm = new UIKeyInput(Event::ID::OPEN_IDENTITY_MENU);
    kidm->place(
        (w - kp->width()) / 2,
        y + 9 * UIKeyInput::Height / 2
    );

    /* ----- POWERS ----- */

    UIKeyInput* ki = new UIKeyInput(Event::ID::INTERACT);
    ki->place(
        (w - kp->width()) / 2,
        y + 13 * UIKeyInput::Height / 2
    );

    UIKeyInput* kbc = new UIKeyInput(Event::ID::BODY_CONTROL);
    kbc->place(
        (w - kp->width()) / 2,
        y + 15 * UIKeyInput::Height / 2
    );

    UIKeyInput* kbr = new UIKeyInput(Event::ID::BODY_RESURRECTION);
    kbr->place(
        (w - kp->width()) / 2,
        y + 17 * UIKeyInput::Height / 2
    );

    /* ----- MOVEMENTS ----- */

    UIKeyInput* kmu = new UIKeyInput(Event::ID::MOVE_UP);
    kmu->place(
        w + (w - kp->width()) / 2,
        y + UIKeyInput::Height / 2
    );
    UIKeyInput* kmd = new UIKeyInput(Event::ID::MOVE_DOWN);
    kmd->place(
        w + (w - kp->width()) / 2,
        y + 3 * UIKeyInput::Height / 2
    );
    UIKeyInput* kml = new UIKeyInput(Event::ID::MOVE_LEFT);
    kml->place(
        w + (w - kp->width()) / 2,
        y + 5 * UIKeyInput::Height / 2
    );
    UIKeyInput* kmr = new UIKeyInput(Event::ID::MOVE_RIGHT);
    kmr->place(
        w + (w - kp->width()) / 2,
        y + 7 * UIKeyInput::Height / 2
    );

    /* ----- DIALOGS ----- */

    UIKeyInput* kvd = new UIKeyInput(Event::ID::VALID_DIALOG);
    kvd->place(
        2 * w + (w - kp->width()) / 2,
        y + UIKeyInput::Height / 2
    );
    UIKeyInput* kna = new UIKeyInput(Event::ID::NEXT_ANSWER);
    kna->place(
        2 * w + (w - kp->width()) / 2,
        y + 3 * UIKeyInput::Height / 2
    );
    UIKeyInput* kpa = new UIKeyInput(Event::ID::PREVIOUS_ANSWER);
    kpa->place(
        2 * w + (w - kp->width()) / 2,
        y + 5 * UIKeyInput::Height / 2
    );

    page["controls"] = {
        {"kp" , kp },
        {"kpm", kpm},
        {"kim", kim},
        {"kqm", kqm},
        {"kidm", kidm},

        {"ki", ki},
        {"kbc", kbc},
        {"kbr", kbr},

        {"kmu", kmu},
        {"kmd", kmd},
        {"kml", kml},
        {"kmr", kmr},

        {"kvd", kvd},
        {"kna", kna},
        {"kpa", kpa}
    };
}

void OptionsMenu::reloadControlsPage() {
    UIKeyInput::Height = (Window::screen.h - border.y - border.h) / 10;

    const int w = Window::screen.w / 3;
    const int y = border.y + border.h;

    /* ----- IDK ----- */

    UIKeyInput* kp = static_cast<UIKeyInput*>(page["controls"]["kp"]);
    kp->reload();
    kp->place(
        (w - kp->width()) / 2,
        y + UIKeyInput::Height / 2
    );

    UIKeyInput* kpm = static_cast<UIKeyInput*>(page["controls"]["kpm"]);
    kpm->reload();
    kpm->place(
        (w - kp->width()) / 2,
        y + 3 * UIKeyInput::Height / 2
    );

    UIKeyInput* kim = static_cast<UIKeyInput*>(page["controls"]["kim"]);
    kim->reload();
    kim->place(
        (w - kp->width()) / 2,
        y + 5 * UIKeyInput::Height / 2
    );

    UIKeyInput* kqm = static_cast<UIKeyInput*>(page["controls"]["kqm"]);
    kqm->reload();
    kqm->place(
        (w - kp->width()) / 2,
        y + 7 * UIKeyInput::Height / 2
    );

    UIKeyInput* kidm = static_cast<UIKeyInput*>(page["controls"]["kidm"]);
    kidm->reload();
    kidm->place(
        (w - kp->width()) / 2,
        y + 9 * UIKeyInput::Height / 2
    );

    /* ----- POWERS ----- */

    UIKeyInput* ki = static_cast<UIKeyInput*>(page["controls"]["ki"]);
    ki->reload();
    ki->place(
        (w - kp->width()) / 2,
        y + 13 * UIKeyInput::Height / 2
    );

    UIKeyInput* kbr = static_cast<UIKeyInput*>(page["controls"]["kbr"]);
    kbr->reload();
    kbr->place(
        (w - kp->width()) / 2,
        y + 15 * UIKeyInput::Height / 2
    );

    UIKeyInput* kbc = static_cast<UIKeyInput*>(page["controls"]["kbc"]);
    kbc->reload();
    kbc->place(
        (w - kp->width()) / 2,
        y + 17 * UIKeyInput::Height / 2
    );

    /* ----- MOVEMENTS ----- */

    UIKeyInput* kmu = static_cast<UIKeyInput*>(page["controls"]["kmu"]);
    kmu->reload();
    kmu->place(
        w + (w - kp->width()) / 2,
        y + UIKeyInput::Height / 2
    );
    UIKeyInput* kmd = static_cast<UIKeyInput*>(page["controls"]["kmd"]);
    kmd->reload();
    kmd->place(
        w + (w - kp->width()) / 2,
        y + 3 * UIKeyInput::Height / 2
    );
    UIKeyInput* kml = static_cast<UIKeyInput*>(page["controls"]["kml"]);
    kml->reload();
    kml->place(
        w + (w - kp->width()) / 2,
        y + 5 * UIKeyInput::Height / 2
    );
    UIKeyInput* kmr = static_cast<UIKeyInput*>(page["controls"]["kmr"]);
    kmr->reload();
    kmr->place(
        w + (w - kp->width()) / 2,
        y + 7 * UIKeyInput::Height / 2
    );

    /* ----- DIALOGS ----- */

    UIKeyInput* kvd = static_cast<UIKeyInput*>(page["controls"]["kvd"]);
    kvd->reload();
    kvd->place(
        2 * w + (w - kp->width()) / 2,
        y + UIKeyInput::Height / 2
    );
    UIKeyInput* kna = static_cast<UIKeyInput*>(page["controls"]["kna"]);
    kna->reload();
    kna->place(
        2 * w + (w - kp->width()) / 2,
        y + 3 * UIKeyInput::Height / 2
    );
    UIKeyInput* kpa = static_cast<UIKeyInput*>(page["controls"]["kpa"]);
    kpa->reload();
    kpa->place(
        2 * w + (w - kp->width()) / 2,
        y + 5 * UIKeyInput::Height / 2
    );
}

void OptionsMenu::init() {
    btn_generalSection = new UIButton(Text::Get("GENERAL"), Event::ID::OPEN_GENERAL_SETTINGS, "h3", hue::font);
    btn_generalSection->place(
        (Window::screen.w / 2 - btn_generalSection->width()) / 2,
        8 * (Window::fullscreen + 1)
    );

    btn_controlsSection = new UIButton(Text::Get("CONTROLS"), Event::ID::OPEN_CONTROLS_SETTINGS, "h3", hue::font);
    btn_controlsSection->place(
        (3 * Window::screen.w / 2 - btn_controlsSection->width()) / 2,
        8 * (Window::fullscreen + 1)
    );

    btn_quit = new UIButton("X", Event::ID::OPEN_MAIN_MENU, "h3", hue::font);
    btn_quit->place(
        Window::screen.w - btn_quit->width() - 8 * (Window::fullscreen + 1),
        8 * (Window::fullscreen + 1)
    );

    border = {
        0,
        8 * (Window::fullscreen + 1) + std::max(btn_generalSection->height(), btn_controlsSection->height()),
        Window::screen.w,
        3 * (Window::fullscreen + 1)
    };

    createGeneralPage();
    createControlsPage();

    usePage("general");
}

void OptionsMenu::update() {
    btn_generalSection->update();
    btn_controlsSection->update();
    btn_quit->update();

    for (const auto& elt : page[currentPage])
        elt.second->update();
}

void OptionsMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::ui_background);

    btn_generalSection->draw();
    btn_controlsSection->draw();
    btn_quit->draw();

    Manager::DrawFilledRect(&border, hue::border);

    for (const auto& elt : page[currentPage])
        elt.second->draw();
}

void OptionsMenu::clean() {
    btn_generalSection->destroy();
    btn_controlsSection->destroy();
    btn_quit->destroy();

    for (auto p : page) {
        for (auto elt : p.second)
            elt.second->destroy();
        p.second.clear();
    }
    page.clear();
}

void OptionsMenu::reload() {
    btn_generalSection->setText(Text::Get("GENERAL"), "h3", hue::white);
    btn_generalSection->place(
        (Window::screen.w / 2 - btn_generalSection->width()) / 2,
        8 * (Window::fullscreen + 1)
    );

    btn_controlsSection->setText(Text::Get("CONTROLS"), "h3", hue::white);
    btn_controlsSection->place(
        (3 * Window::screen.w / 2 - btn_controlsSection->width()) / 2,
        8 * (Window::fullscreen + 1)
    );

    btn_quit->setText("X", "h3", hue::white);
    btn_quit->place(
        Window::screen.w - btn_quit->width() - 8 * (Window::fullscreen + 1),
        8 * (Window::fullscreen + 1)
    );

    border = {
        0,
        8 * (Window::fullscreen + 1) + std::max(btn_generalSection->height(), btn_controlsSection->height()),
        Window::screen.w,
        3 * (Window::fullscreen + 1)
    };

    reloadGeneralPage();
    reloadControlsPage();
}

void OptionsMenu::usePage(const std::string& p) {
    currentPage = p;
}

void OptionsMenu::next(const std::string& cmd) {
    if (cmd == "window mode") {
        UIWindowModeSelector* wms = static_cast<UIWindowModeSelector*>(page["general"]["wms"]);
        wms->next();
        return;
    }

    if (cmd == "language") {
        UILanguageSelector* lgs = static_cast<UILanguageSelector*>(page["general"]["lgs"]);
        lgs->next();
        return;
    }
}
