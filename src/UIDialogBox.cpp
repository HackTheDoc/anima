#include "include/UI/UIDialogBox.h"

#include "include/Window.h"

UIDialogBox::UIDialogBox(const std::string& ownerName, const std::string& text) {
    rect.w = 15 * Window::screen.w / 16;
    rect.h = rect.w / 5;

    lbl_owner = new UILabel((ownerName + " :").c_str(), "default bold", hue::font);
    lbl_content = new UILabel();

    setText(text);
}

UIDialogBox::~UIDialogBox() {}

void UIDialogBox::draw() {
    Manager::DrawFilledRect(&rect, hue::text_box);

    lbl_owner->draw();

    if (haveContent)
        lbl_content->draw();

    Manager::DrawRect(&rect, hue::border);
}

void UIDialogBox::destroy() {
    lbl_owner->destroy();
    lbl_content->destroy();
}

void UIDialogBox::setText(const std::string& text) {
    if (text.size() == 0) {
        haveContent = false;
        lbl_content->destroy();
        return;
    }

    haveContent = true;
    lbl_content->setText(text, "default", hue::font, rect.w - 2 * 26);
}

void UIDialogBox::place() {
    rect.x = (Window::screen.w - rect.w) / 2;
    rect.y = Window::screen.h - rect.h - rect.x / 2;

    lbl_owner->place(
        rect.x + 26 * (Window::fullscreen + 1),
        rect.y + 8 * (Window::fullscreen + 1)
    );

    lbl_content->place(
        rect.x + 26 * (Window::fullscreen + 1),
        lbl_owner->y() + lbl_owner->height()
    );
}
