#include "include/GifTexture.h"

#include "include/Manager.h"

GifTexture::GifTexture(std::string path, int f, int s, SDL_Rect dest) {
    currentFrame = 0;
    numberOfFrames = f;
    speed = s;
    destRect = dest;

    for (int i = 1; i <= numberOfFrames; i++) {
        SDL_Texture* t = Manager::LoadTexture((path+"/"+std::to_string(i)+".png").c_str());
        frames.push_back(t);
    }
}

GifTexture::~GifTexture() {}

void GifTexture::play() {
    currentFrame = static_cast<int>( (SDL_GetTicks() / speed) % numberOfFrames );
}

void GifTexture::draw() {
    if (frames.empty())
        return;
        
    Manager::Draw(frames[currentFrame], nullptr, &destRect);
}

void GifTexture::destroy() {
    for (auto f : frames) {
        SDL_DestroyTexture(f);
    }
    frames.clear();
}
