#include "include/WindowState/Cinematic.h"

#include "include/Text.h"
#include "include/Window.h"
#include "include/Manager.h"

constexpr std::chrono::milliseconds TRANSITION_DURATION(1000);
constexpr std::chrono::milliseconds TRANSITION_OUT_DURATION(2000);
constexpr std::chrono::milliseconds TEXT_DURATION(3000);

Cinematic::Cinematic(const std::string& tag) : tag(tag) {}

Cinematic::~Cinematic() {}

void Cinematic::init() {
    const std::vector<std::string> sentences = Text::GetCinematic(tag);

    for (const std::string& s : sentences) {
        UILabel* l = new UILabel(s, "big", hue::white, Window::screen.w, true);
        l->place(
            (Window::screen.w - l->width() ) / 2,
            (Window::screen.h - l->height()) / 2
        );
        texts.push_back(l);
    }
    
    curr = 0;

    opacity = 0;

    startTime = std::chrono::steady_clock::now();
}

void Cinematic::update() {
    const TimePoint currTime = std::chrono::steady_clock::now();
    const std::chrono::milliseconds elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currTime-startTime);

    if (curr < texts.size()) {
        if (elapsedTime < TRANSITION_DURATION)
            opacity = 255 - (elapsedTime.count() * 255 / TRANSITION_DURATION.count());
        else
            opacity = 0;

        if (elapsedTime > TRANSITION_DURATION + TEXT_DURATION)
            opacity = elapsedTime.count() * 255 / TRANSITION_DURATION.count();
        if (elapsedTime > 2*TRANSITION_DURATION + TEXT_DURATION && curr < texts.size()) {
            curr++;
            startTime = currTime;
        }
    }
    else {
        if (elapsedTime < TRANSITION_OUT_DURATION) {
            opacity = 255 - (elapsedTime.count() * 255 / TRANSITION_OUT_DURATION.count());

            WindowState* g = Window::manager->getState(WindowState::Type::GAME);
            g->update();
        }
        else
            Window::manager->setCurrentWindowState(WindowState::GAME);
    }
}

void Cinematic::render() {
    if (curr < texts.size()) {
        Manager::DrawFilledRect(&Window::screen, hue::cinematic_background);
        texts[curr]->draw();
    }
    else {
        WindowState* g = Window::manager->getState(WindowState::Type::GAME);
        g->render();
    }

    SDL_Color c = hue::cinematic_background;
    c.a = opacity;
    Manager::DrawFilledRect(&Window::screen, c);
}

void Cinematic::clean() {
    for (auto l : texts)
        l->destroy();
    texts.clear();
}
