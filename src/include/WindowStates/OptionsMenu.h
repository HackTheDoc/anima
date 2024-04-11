#pragma once

#include <map>
#include <vector>
#include <string>

#include "WindowState.h"

#include "../UI/UIElements.h"

class OptionsMenu : public WindowState {
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
    void usePage(const std::string& p);

    /// @brief change a selector's current choice to the next one
    /// @param cmd name of the selector to update
    void next(const std::string& cmd);

private:
    UIButton* btn_quit;
    UIButton* btn_generalSection;
    UIButton* btn_controlsSection;

    SDL_Rect border;

    std::map<std::string, std::map<std::string, UIElement*>> page;
    std::string currentPage;

    void createGeneralPage();
    void createControlsPage();

    void reloadGeneralPage();
    void reloadControlsPage();
};
