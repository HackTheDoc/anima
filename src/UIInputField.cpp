#include "include/UI/UIInputField.h"

#include "include/Window.h"
#include "include/Manager.h"

UIInputField::UIInputField(std::string title_text, std::string placeholder_text, UIButton::ID id, int max) {
    input = "";
    inputLengthMax = max;
    actived = false;

    title = new UILabel(title_text, "h2", hue::font);

    placeholder = new UILabel(placeholder_text, "h4", hue::placeholder_text);

    text = new UILabel("", "h4", hue::font);

    btn = new UIButton(Text::Get("Valid"), id, "h3", hue::font);

    int cw, ch;
    TTF_SizeUTF8(Window::manager->getFont("h4"), "W", &cw, &ch);

    inputRect.w = cw * max + 16*(Window::fullscreen+1);
    inputRect.h = ch + 32*(Window::fullscreen+1);

    rect.h = title->height() + btn->height() + inputRect.h +   96*(Window::fullscreen+1);
    rect.w = inputRect.w + 64*(Window::fullscreen+1); 

    place(0,0);
}

UIInputField::~UIInputField() {}

void UIInputField::update() {
    SDL_Point m;
    SDL_GetMouseState(&m.x, &m.y);
    if (!SDL_PointInRect(&m, &rect) && Window::event.mouseClickLeft()) {
        Window::event.handleButtonClick(UIButton::ID::QUIT_WORLD_NAME_INPUT);
        return;
    }

    if ((int)input.size() < inputLengthMax && Window::event.e.type == SDL_TEXTINPUT) {
        input += Window::event.e.text.text;
    }
    else if (!input.empty()) {
        if (Window::event.e.type == SDL_KEYDOWN && Window::event.e.key.keysym.sym == SDLK_BACKSPACE) {
            input.pop_back();
        }

        text->setText(input, "h4", hue::font);
        text->place(
            inputRect.x + 2*(Window::fullscreen),
            inputRect.y + (inputRect.h - text->height()) / 2
        );
    }

    if (Window::event.e.type == SDL_KEYUP && Window::event.e.key.keysym.sym == SDLK_RETURN) {
        Window::event.handleButtonClick(btn->getID());
    }

    btn->update();
}

void UIInputField::draw() {
    Manager::DrawFilledRect(&rect, hue::blur_dark);

    title->draw();

    if (input.empty())
        placeholder->draw();
    else
        text->draw();
    
    Manager::DrawRect(&inputRect, hue::border);

    btn->draw();

    Manager::DrawRect(&rect, hue::border);
}

void UIInputField::destroy() {
    title->destroy();

    placeholder->destroy();

    text->destroy();

    btn->destroy();
}

void UIInputField::place(int x, int y) {
    rect.x = x;
    rect.y = y;

    title->place(
        x + (rect.w - title->width()) / 2,
        y + 24*(Window::fullscreen+1)
    );

    btn->place(
        x + (rect.w - btn->width()) / 2,
        y + rect.h - btn->height() - 24*(Window::fullscreen+1)
    );

    inputRect.x = x + (rect.w - inputRect.w) / 2;
    inputRect.y = title->y() + title->height() + 24*(Window::fullscreen+1);

    placeholder->place(
        inputRect.x + 2*(Window::fullscreen+1),
        inputRect.y + (inputRect.h - placeholder->height()) / 2
    );
}