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

    void place(const int x, const int y);

    void reload();

private:
    /// @brief to convert boolean to string
    const std::string vstring[2] = {"Off", "On"};

    UILabel* title;
    UILabel* value;

    std::string tag;
    bool* var;
};
