#pragma once

#include "UIElement.h"
#include "UILabel.h"

class UIActivator : public UIElement {
public:
    UIActivator(const std::string& t, bool* v);
    ~UIActivator();

    void draw() override;
    void update() override;
    void destroy() override;

    /// @brief place at a precise position
    /// @param x x pos in pixels
    /// @param y y pos in pixels
    void place(int x, int y);

    /// @brief reload the textures
    void reload();

private:
    /// @brief to convert boolean to string
    const std::string vstring[2] = {"Off", "On"};

    UILabel* title;
    UILabel* value;

    std::string tag;
    bool* var;
};
