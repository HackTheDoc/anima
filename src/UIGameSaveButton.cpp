#include "include/UI/UIGameSaveButton.h"

#include "include/Window.h"
#include "include/Save.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

UIGameSaveButton::UIGameSaveButton(std::string sname, int sid, UIButton::ID id, std::string font, const SDL_Color& color) {
    this->id = id;
    hovered = actived = false;

    texture = Manager::GenerateText(
        sname.c_str(),
        Window::manager->getFont(font),
        color);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

    hoveredTexture = Manager::GenerateText(
        (sname + " <").c_str(),
        Window::manager->getFont(font + " bold"),
        color);
    SDL_QueryTexture(hoveredTexture, NULL, NULL, &hoveredTextureRect.w, &hoveredTextureRect.h);

    // info
    if (!Save::Exist(sid)) {
        info = nullptr;
        return;
    }

    std::ifstream infile("./config.json");
    json config;
    infile >> config;
    infile.close();

    std::string wname = config["world "+std::to_string(sid)+" name"];
    std::string wtime = config["world "+std::to_string(sid)+" time"];

    info = new UITextBox(wname+" ("+wtime+")", "default", hue::white); 

    place(0, 0);
}

UIGameSaveButton::~UIGameSaveButton() {}

void UIGameSaveButton::draw() {
    if (actived || hovered)
        Manager::Draw(hoveredTexture, nullptr, &hoveredTextureRect);
    else
        Manager::Draw(texture, nullptr, &rect);
    
    if (hovered && info != nullptr) {
        info->draw();
    }
}

void UIGameSaveButton::update() {
    SDL_Point m;
    SDL_GetMouseState(&m.x, &m.y);

    hovered = SDL_PointInRect(&m, &rect);

    if (info != nullptr && hovered) {
        info->place(m.x, m.y);
    }

    if (Window::event.mouseClickLeft()) {
        if (hovered) {
            Window::event.handleButtonClick(id);
            actived = true;
        }
        else
            actived = false;
    }
}

void UIGameSaveButton::destroy() {
    UIButton::destroy();

    if (info == nullptr) return;

    info->destroy();
}

void UIGameSaveButton::place(int x, int y) {
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
