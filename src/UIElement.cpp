#include "include/UI/UIElement.h"

#include "include/Window.h"

const int UIElement::MARGIN = 4;

void UIElement::draw() {}

void UIElement::update() {}

void UIElement::destroy() {}

void UIElement::place(const int x, const int y) {
    rect.x = x;
    rect.y = y;
}

void UIElement::placeLeft(int y, const int span) {
    if (y == -1) y = (Window::screen.h - rect.h) / 2;

    place(Window::screen.w - rect.w - span, y);
}

void UIElement::placeBottom(int x) {
    if (x == -1) rect.x = (Window::screen.w - rect.w) / 2;

    place(x, Window::screen.h - rect.h - 4);
}

int UIElement::x() {
    return rect.x;
}

int UIElement::y() {
    return rect.y;
}

int UIElement::width() {
    return rect.w;
}

int UIElement::height() {
    return rect.h;
}
