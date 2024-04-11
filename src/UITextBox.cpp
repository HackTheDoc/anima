#include "include/UI/UITextBox.h"

#include "include/Window.h"

UITextBox::UITextBox(const std::string& text, const std::string& font, const SDL_Color& color) {
    lbl = new UILabel(text, font, color);
    rect.w = lbl->width() + 2 * UIElement::MARGIN * (Window::fullscreen + 1);
    rect.h = lbl->height() + 2 * UIElement::MARGIN * (Window::fullscreen + 1);

    place(0, 0);
}

UITextBox::UITextBox(const std::string& text, const std::string& font, const SDL_Color& color, const int mlength) {
    lbl = new UILabel(text, font, color, mlength);
    rect.w = lbl->width() + 2 * UIElement::MARGIN * (Window::fullscreen + 1);
    rect.h = lbl->height() + 2 * UIElement::MARGIN * (Window::fullscreen + 1);

    place(0, 0);
}

UITextBox::~UITextBox() {}

void UITextBox::draw() {
    Manager::DrawFilledRect(&rect, hue::ui_background);
    lbl->draw();
    Manager::DrawRect(&rect, hue::white);
}

void UITextBox::destroy() {
    lbl->destroy();
}

void UITextBox::place(const int x, const int y) {
    rect.x = x;
    rect.y = y;

    lbl->place(x + UIElement::MARGIN * (Window::fullscreen + 1), y + UIElement::MARGIN * (Window::fullscreen + 1));
}

void UITextBox::setText(const std::string& text, const std::string& font, const SDL_Color& color) {
    lbl->setText(text, font, color);

    rect.w = lbl->width() + 2 * UIElement::MARGIN * (Window::fullscreen + 1);
    rect.h = lbl->height() + 2 * UIElement::MARGIN * (Window::fullscreen + 1);
}

void UITextBox::setText(const std::string& text, const std::string& font, const SDL_Color& color, const int mlength) {
    lbl->setText(text, font, color, mlength);

    rect.w = lbl->width() + 2 * UIElement::MARGIN * (Window::fullscreen + 1);
    rect.h = lbl->height() + 2 * UIElement::MARGIN * (Window::fullscreen + 1);
}
