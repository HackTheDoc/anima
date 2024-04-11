#include "include/UI/UIGifTexture.h"

#include "include/Manager.h"

UIGifTexture::UIGifTexture(const std::string& path, const int f, const int s, const SDL_Rect& dest) {
    currentFrame = 0;
    numberOfFrames = f;
    speed = s;
    rect = dest;

    for (int i = 1; i <= numberOfFrames; i++) {
        SDL_Texture* t = Manager::LoadTexture((path + "/" + std::to_string(i) + ".png").c_str());
        frames.push_back(t);
    }
}

UIGifTexture::~UIGifTexture() {}

void UIGifTexture::update() {
    currentFrame = static_cast<int>((SDL_GetTicks() / speed) % numberOfFrames);
}

void UIGifTexture::draw() {
    if (frames.empty())
        return;

    Manager::Draw(frames[currentFrame], nullptr, &rect);
}

void UIGifTexture::destroy() {
    for (auto f : frames) {
        SDL_DestroyTexture(f);
    }
    frames.clear();
}
