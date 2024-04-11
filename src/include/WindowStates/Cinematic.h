#pragma once

#include "WindowState.h"

#include "../UI/UIElements.h"

#include <chrono>

using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

class Cinematic : public WindowState {
public:
    Cinematic(const std::string& tag);
    ~Cinematic();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

private:
    const std::string tag;

    std::vector<UILabel*> texts;
    size_t curr;
    Uint8 opacity;

    TimePoint startTime;
};
