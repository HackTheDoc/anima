#pragma once

#include "UIElement.h"
#include "UILabel.h"

#include "../Event.h"

class UIKeyInput : public UIElement {
public:
    static int Height;

    UIKeyInput(const Event::ID eid);

    ~UIKeyInput();

    void draw() override;
    void update() override;
    void destroy() override;

    void reload();

    void place(const int x, const int y);

private:
    bool actived;
    
    UILabel* lbl_title;

    /// @brief set the title depending on the registered event id
    void setTitle();

    UILabel* lbl_key;

    /// @brief associate a new key to the event id
    void setKey();

    /// @brief id of the event associated to the key input
    Event::ID eid;
};
