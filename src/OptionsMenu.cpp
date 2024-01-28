#include "include/WindowState/OptionsMenu.h"

#include "include/Window.h"
#include "include/Manager.h"

#include "include/UI/UIElements.h"

OptionsMenu::OptionsMenu() {}

OptionsMenu::~OptionsMenu() {}

void OptionsMenu::createGeneralPage() {
    UIWindowModeSelector* wms = new UIWindowModeSelector();
    wms->place(
        (Window::screen.w - wms->width()) / 2,
        border.y + 32*(Window::fullscreen+1)
    );

    UILanguageSelector* lgs = new UILanguageSelector();
    lgs->place(
        (Window::screen.w - lgs->width()) / 2,
        wms->y() + wms->height() + 32*(Window::fullscreen+1)
    );

    UISaveModeSelector* sms = new UISaveModeSelector();
    sms->place(
        (Window::screen.w - sms->width()) / 2,
        lgs->y() + lgs->height() + 32*(Window::fullscreen+1)
    );
    
    page["general"] = {
        wms,
        lgs,
        sms
    };
}

void OptionsMenu::reloadGeneralPage() {
    UIWindowModeSelector* wms = static_cast<UIWindowModeSelector*>(page["general"][0]);
    wms->reload();
    wms->place(
        (Window::screen.w - wms->width()) / 2,
        border.y + 32*(Window::fullscreen+1)
    );

    UILanguageSelector* lgs = static_cast<UILanguageSelector*>(page["general"][1]);
    lgs->reload();
    lgs->place(
        (Window::screen.w - lgs->width()) / 2,
        wms->y() + wms->height() + 32*(Window::fullscreen+1)
    );


    UISaveModeSelector* sms = static_cast<UISaveModeSelector*>(page["general"][2]);
    sms->reload();
    sms->place(
        (Window::screen.w - sms->width()) / 2,
        lgs->y() + lgs->height() + 32*(Window::fullscreen+1)
    );
}

void OptionsMenu::createControlsPage() {
    UIKeyInput::Height = (Window::screen.h - border.y - border.h) / 10; 

    int w = Window::screen.w / 3;
    int y = border.y + border.h;

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

    UIKeyInput* ki = new UIKeyInput(Event::ID::INTERACT);
    ki->place(
        (w - kp->width()) / 2,
        y + 9 * UIKeyInput::Height / 2
    );

    /* ----- POWERS ----- */

    UIKeyInput* kbc = new UIKeyInput(Event::ID::BODY_CONTROL);
    kbc->place(
        (w - kp->width()) / 2,
        y + 11 * UIKeyInput::Height / 2
    );

    UIKeyInput* kbr = new UIKeyInput(Event::ID::BODY_RESURRECTION);
    kbr->place(
        (w - kp->width()) / 2,
        y + 13 * UIKeyInput::Height / 2
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
        2*w + (w - kp->width()) / 2,
        y + UIKeyInput::Height / 2
    );
    UIKeyInput* kna = new UIKeyInput(Event::ID::NEXT_ANSWER);
    kna->place(
        2*w + (w - kp->width()) / 2,
        y + 3 * UIKeyInput::Height / 2
    );
    UIKeyInput* kpa = new UIKeyInput(Event::ID::PREVIOUS_ANSWER);
    kpa->place(
        2*w + (w - kp->width()) / 2,
        y + 5 * UIKeyInput::Height / 2
    );

    page["controls"] = {
        kp,
        kpm,
        kim,

        ki,
        kbc,
        kbr,

        kmu,
        kmd,
        kml,
        kmr,

        kvd,
        kna,
        kpa
    };
}

void OptionsMenu::reloadControlsPage() {
    UIKeyInput::Height = (Window::screen.h - border.y - border.h) / 10;
    
    int w = Window::screen.w / 3;
    int y = border.y + border.h;

    /* ----- IDK ----- */

    UIKeyInput* kp = static_cast<UIKeyInput*>(page["controls"][0]);
    kp->reload();
    kp->place(
        (w - kp->width()) / 2,
        y + UIKeyInput::Height / 2
    );

    UIKeyInput* kpm = static_cast<UIKeyInput*>(page["controls"][1]);
    kpm->reload();
    kpm->place(
        (w - kp->width()) / 2,
        y + 3 * UIKeyInput::Height / 2
    );

    UIKeyInput* kim = static_cast<UIKeyInput*>(page["controls"][2]);
    kim->place(
        (w - kp->width()) / 2,
        y + 5 * UIKeyInput::Height / 2
    );

    UIKeyInput* ki = static_cast<UIKeyInput*>(page["controls"][3]);
    ki->reload();
    ki->place(
        (w - kp->width()) / 2,
        y + 9 * UIKeyInput::Height / 2
    );

    /* ----- POWERS ----- */

    UIKeyInput* kbr = static_cast<UIKeyInput*>(page["controls"][4]);
    kbr->reload();
    kbr->place(
        (w - kp->width()) / 2,
        y + 11 * UIKeyInput::Height / 2
    );

    UIKeyInput* kbc = static_cast<UIKeyInput*>(page["controls"][5]);
    kbc->place(
        (w - kp->width()) / 2,
        y + 13 * UIKeyInput::Height / 2
    );

    /* ----- MOVEMENTS ----- */

    UIKeyInput* kmu = static_cast<UIKeyInput*>(page["controls"][6]);
    kmu->reload();
    kmu->place(
        w + (w - kp->width()) / 2,
        y + UIKeyInput::Height / 2
    );
    UIKeyInput* kmd = static_cast<UIKeyInput*>(page["controls"][7]);
    kmd->reload();
    kmd->place(
        w + (w - kp->width()) / 2,
        y + 3 * UIKeyInput::Height / 2
    );
    UIKeyInput* kml = static_cast<UIKeyInput*>(page["controls"][8]);
    kml->reload();
    kml->place(
        w + (w - kp->width()) / 2,
        y + 5 * UIKeyInput::Height / 2
    );
    UIKeyInput* kmr = static_cast<UIKeyInput*>(page["controls"][9]);
    kmr->reload();
    kmr->place(
        w + (w - kp->width()) / 2,
        y + 7 * UIKeyInput::Height / 2
    );

    /* ----- DIALOGS ----- */
    
    UIKeyInput* kvd = static_cast<UIKeyInput*>(page["controls"][10]);
    kvd->reload();
    kvd->place(
        2*w + (w - kp->width()) / 2,
        y + UIKeyInput::Height / 2
    );
    UIKeyInput* kna = static_cast<UIKeyInput*>(page["controls"][11]);
    kna->reload();
    kna->place(
        2*w + (w - kp->width()) / 2,
        y + 3 * UIKeyInput::Height / 2
    );
    UIKeyInput* kpa = static_cast<UIKeyInput*>(page["controls"][12]);
    kpa->reload();
    kpa->place(
        2*w + (w - kp->width()) / 2,
        y + 5 * UIKeyInput::Height / 2
    );
}

void OptionsMenu::init() {
    button[GENERAL] = new UIButton(Text::Get("GENERAL"), UIButton::ID::GENERAL_SETTINGS, "h3", hue::white);
    button[GENERAL]->place(
        (Window::screen.w / 2 - button[GENERAL]->width()) / 2,
        8*(Window::fullscreen+1)
    );

    button[CONTROLS] = new UIButton(Text::Get("CONTROLS"), UIButton::ID::CONTROLS_SETTINGS, "h3", hue::white);
    button[CONTROLS]->place(
        (3 * Window::screen.w / 2 - button[CONTROLS]->width()) / 2,
        8*(Window::fullscreen+1)
    );

    button[QUIT] = new UIButton("X", UIButton::ID::QUIT_SETTINGS, "h3", hue::white);
    button[QUIT]->place(
        Window::screen.w - button[QUIT]->width() - 8*(Window::fullscreen+1),
        8*(Window::fullscreen+1)
    );

    border = {
        0,
        8*(Window::fullscreen+1) + std::max(button[GENERAL]->height(), button[CONTROLS]->height()),
        Window::screen.w,
        3*(Window::fullscreen+1)
    };

    createGeneralPage();
    createControlsPage();

    usePage("general");
}

void OptionsMenu::update() {
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
        button[i]->update();

    for (auto elt : page[currentPage])
        elt->update();
}

void OptionsMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::ui_background);

    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
        button[i]->draw();

    /// TODO: change color
    Manager::DrawFilledRect(&border, hue::white);

    for (auto elt : page[currentPage])
        elt->draw();
}

void OptionsMenu::clean() {
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++) {
        button[i]->destroy();
    }

    for (auto p : page) {
        for (auto elt : p.second)
            elt->destroy();
        p.second.clear();
    }
    page.clear();
}

void OptionsMenu::reload() {
    button[GENERAL]->setText(Text::Get("GENERAL"), "h3", hue::white);
    button[GENERAL]->place(
        (Window::screen.w / 2 - button[GENERAL]->width()) / 2,
        8*(Window::fullscreen+1)
    );

    button[CONTROLS]->setText(Text::Get("CONTROLS"), "h3", hue::white);
    button[CONTROLS]->place(
        (3 * Window::screen.w / 2 - button[CONTROLS]->width()) / 2,
        8*(Window::fullscreen+1)
    );

    button[QUIT]->setText("X", "h3", hue::white);
    button[QUIT]->place(
        Window::screen.w - button[QUIT]->width() - 8*(Window::fullscreen+1),
        8*(Window::fullscreen+1)
    );

    border = {
        0,
        8*(Window::fullscreen+1) + std::max(button[GENERAL]->height(), button[CONTROLS]->height()),
        Window::screen.w,
        3*(Window::fullscreen+1)
    };

    reloadGeneralPage();
    reloadControlsPage();
}

void OptionsMenu::usePage(std::string p) {
    currentPage = p;
}

void OptionsMenu::next(std::string cmd) {
    if (cmd == "window mode") {
        UIWindowModeSelector* wms = static_cast<UIWindowModeSelector*>(page["general"][0]);
        wms->next();
        return;
    }

    if (cmd == "language") {
        UILanguageSelector* ls = static_cast<UILanguageSelector*>(page["general"][1]);
        ls->next();
        return;
    }
}
