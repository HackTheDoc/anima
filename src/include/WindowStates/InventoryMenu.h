#pragma once

#include <vector>

#include "WindowState.h"

#include "../UI/UIElements.h"

class Entity;
struct Inventory;

class InventoryMenu : public WindowState {
public:
    InventoryMenu(Inventory* inv);
    ~InventoryMenu();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

private:
    SDL_Rect container;

    UILabel* lbl_title;
    UILabel* lbl_usage;

    Inventory* inventory;
    std::vector<SDL_Rect> itemRect;

    UITextBox* itemDescription;

    void prepareSize1();
    void prepareSize2();
    void prepareSize4();
    void prepareSize6();
};
