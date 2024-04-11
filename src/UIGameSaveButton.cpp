#include "include/UI/UIGameSaveButton.h"

#include "include/Window.h"
#include "include/Manager.h"
#include "include/Save.h"

#include <fstream>
#include <iostream>

using json = nlohmann::json;

UIGameSaveButton::UIGameSaveButton(const std::string& saveName, int sid, const Event::ID eid, const std::string& font, const SDL_Color& color) {
    this->eid = eid;
    hovered = actived = false;

    texture = Manager::GenerateText(saveName.c_str(), font, color);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    hoveredTexture = Manager::GenerateText((saveName + " <").c_str(), font + " bold", color);
    SDL_QueryTexture(hoveredTexture, NULL, NULL, &hoveredTextureRect.w, &hoveredTextureRect.h);

    // info
    if (!Save::Exist(sid)) {
        info = nullptr;
        place(0, 0);
        return;
    }

    std::pair<std::string, std::string> winfo = Save::GetWorldInfo(sid);

    info = new UITextBox(winfo.first + " (" + winfo.second + ")", "default", hue::white);

    place(0, 0);
}

UIGameSaveButton::~UIGameSaveButton() {}

void UIGameSaveButton::draw() {
    if (actived || hovered)
        Manager::Draw(hoveredTexture, nullptr, &hoveredTextureRect);
    else
        Manager::Draw(texture, nullptr, &rect);

    if (hovered && info != nullptr)
        info->draw();
}

void UIGameSaveButton::update() {
    SDL_Point m;
    SDL_GetMouseState(&m.x, &m.y);

    hovered = SDL_PointInRect(&m, &rect);

    if (info != nullptr && hovered)
        info->place(m.x, m.y);

    if (Window::event.mouseClickLeft()) {
        if (hovered) {
            Window::event.raise(eid);
            actived = true;
        }
        else actived = false;
    }
}

void UIGameSaveButton::destroy() {
    UIButton::destroy();

    if (info == nullptr) return;

    info->destroy();
}

void UIGameSaveButton::place(const int x, const int y) {
    rect.x = x;
    rect.y = y;

    hoveredTextureRect.x = x;
    hoveredTextureRect.y = y;
}

bool UIGameSaveButton::isActive() {
    return actived;
}

void UIGameSaveButton::removeInfos() {
    if (info == nullptr) return;

    info->destroy();
    info = nullptr;
}
