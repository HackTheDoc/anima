#include "include/UI/UIPopUp.h"

#include "include/Window.h"

const int UIPopUp::DELAY = 90;

UIPopUp::UIPopUp()
    : timeLeft(0)
    , haveBlur(false)
    , lbl(nullptr)
    {}

UIPopUp::~UIPopUp() {}

void UIPopUp::addBlur() {
    haveBlur = true;
}

void UIPopUp::addLabel(std::string t) {
    lbl = new UILabel(
        Text::Get(t).c_str(),
        "big",
        hue::black
    );
    rect = {
        (Window::screen.w - lbl->width()) / 2,
        Window::screen.h - lbl->height() - 16*(Window::fullscreen+1),
        lbl->width(),
        lbl->height()
    };
}

void UIPopUp::draw(int offset) {
    timeLeft--;

    if (haveBlur)
        Manager::DrawFilledRect(&Window::screen, hue::blur_white);
    
    if (lbl) {
        rect.y -= offset;
        Manager::SetViewport(&rect);
        lbl->draw();
        Manager::SetViewport(nullptr);
        rect.y += offset;
    }
}

void UIPopUp::destroy() {
    haveBlur = false;

    if (lbl) lbl->destroy();
}

bool UIPopUp::operator<(const UIPopUp* o) const {
    return timeLeft > o->timeLeft;
}
