#include "include/UI/UIHyperlink.h"

#include "include/Window.h"
#include "include/Manager.h"
#include "include/Manager.h"

UIHyperlink::UIHyperlink(std::string text, std::string url, std::string font, const SDL_Color& color) {
    this->url = url;

    texture = Manager::GenerateText(
        text.c_str(),
        Window::manager->getFont(font),
        color);
    rect = {0, 0, 0, 0};
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    cursorRect[0] = {0, 0, 0, 0};
    cursor[0] = Manager::GenerateText(
        ">",
        Window::manager->getFont(font+" bold"),
        color
    );
    SDL_QueryTexture(cursor[0], NULL, NULL, &cursorRect[0].w, &cursorRect[0].h);

    cursorRect[1] = {0, 0, 0, 0};
    cursor[1] = Manager::GenerateText(
        "<",
        Window::manager->getFont(font + " bold"),
        color);
    SDL_QueryTexture(cursor[1], NULL, NULL, &cursorRect[1].w, &cursorRect[1].h);

    actived = false;
}

UIHyperlink::~UIHyperlink() {}

void UIHyperlink::place(int x, int y) {
    UIElement::place(x, y);

    cursorRect[0].x = rect.x - cursorRect[0].w - 2 * (Window::fullscreen + 1);
    cursorRect[0].y = rect.y;

    cursorRect[1].x = rect.x + rect.w + 2 * (Window::fullscreen + 1);
    cursorRect[1].y = rect.y;
}

void UIHyperlink::draw() {
    Manager::Draw(texture, nullptr, &rect);

    if (actived) {
        Manager::Draw(cursor[0], nullptr, &cursorRect[0]);
        Manager::Draw(cursor[1], nullptr, &cursorRect[1]);
    }
}

void UIHyperlink::update() {
    SDL_Point m;
    SDL_GetMouseState(&m.x, &m.y);

    actived = SDL_PointInRect(&m, &rect);

    if (actived && Window::event.mouseClickLeft())
        openURL();
}

void UIHyperlink::destroy() {
    SDL_DestroyTexture(texture);
    texture = nullptr;

    SDL_DestroyTexture(cursor[0]);
    cursor[0] = nullptr;

    SDL_DestroyTexture(cursor[1]);
    cursor[1] = nullptr;
}

void UIHyperlink::openURL() {
#ifdef _WIN32
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
#elif __APPLE__
    std::string cmd = "open \"" + url + "\"";
    system(cmd.c_str());
#else
    std::string cmd = "xdg-open \"" + url + "\"";
    system(cmd.c_str());
#endif
}
