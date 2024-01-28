#pragma once

#include <map>
#include <vector>
#include <string>

#include "WindowState.h"

#include "../UI/UIElements.h"

class OptionsMenu : public WindowState {
private:
    enum buttons {
        QUIT,
        GENERAL,
        CONTROLS,
        NUMBER_OF_BUTTONS
    };
    UIButton* button[NUMBER_OF_BUTTONS];
    SDL_Rect border;

    std::map<std::string, std::vector<UIElement*>> page;
    std::string currentPage;

    void createGeneralPage();
    void createControlsPage();

    void reloadGeneralPage();
    void reloadControlsPage();

public:
    OptionsMenu();
    ~OptionsMenu();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void reload() override;

    /// @brief change current page of selections
    /// @param p format : ["general", "controls"]
    void usePage(std::string p);

    /// @brief change a selector's current choice to the next one
    /// @param cmd name of the selector to update
    void next(std::string cmd);
};
