#include "include/UI/UITextBox.h"

#include "include/Window.h"
#include "include/Manager.h"

UITextBox::UITextBox(std::string t, std::string font, const SDL_Color& color) {
    text = new UILabel(t, font, color);
    rect.w = text->width() + 2*UIElement::MARGIN*(Window::fullscreen+1);
    rect.h = text->height() + 2*UIElement::MARGIN*(Window::fullscreen+1);

    place(0,0);
}

UITextBox::UITextBox(std::string t, std::string font, const SDL_Color& color, int mlength) {
    text = new UILabel(t, font, color, mlength);
    rect.w = text->width() + 2*UIElement::MARGIN*(Window::fullscreen+1);
    rect.h = text->height() + 2*UIElement::MARGIN*(Window::fullscreen+1);

    place(0,0);
}

UITextBox::~UITextBox() {}

void UITextBox::draw() {
    Manager::DrawFilledRect(&rect, hue::ui_background);
    text->draw();
    Manager::DrawRect(&rect, hue::white);
}

void UITextBox::destroy() {
    text->destroy();
}

void UITextBox::place(int x, int y) {
    rect.x = x;
    rect.y = y;

    text->place(x+UIElement::MARGIN*(Window::fullscreen+1), y+UIElement::MARGIN*(Window::fullscreen+1));
}

void UITextBox::setText(std::string t, std::string font, const SDL_Color& color) {
    text->setText(t, font, color);

    rect.w = text->width() + 2*UIElement::MARGIN*(Window::fullscreen+1);
    rect.h = text->height() + 2*UIElement::MARGIN*(Window::fullscreen+1);
}

void UITextBox::setText(std::string t, std::string font, const SDL_Color& color, int mlength) {
    text->setText(t, font, color, mlength);

    rect.w = text->width() + 2*UIElement::MARGIN*(Window::fullscreen+1);
    rect.h = text->height() + 2*UIElement::MARGIN*(Window::fullscreen+1);
}
