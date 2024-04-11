#pragma once

#include "WindowState.h"

#include "../UI/UIElements.h"

class PlayMenu : public WindowState {
public:
    PlayMenu();
    ~PlayMenu();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

    static bool IsSelectionActived();

    static void RemoveInfos(const int saveID);

    /// @brief id of the selected world (1-4)
    static int Selection;

    static void OpenWorldNameInput();
    static void CloseWorldNameInput();

    /// @brief push the name from the input field to Game::WorldName variable
    static void ValidWorldName();
    
private:
    UIGifTexture* gif_background;

    UILabel* lbl_title;

    static UIGameSaveButton* btn_game[4];

    UIButton* btn_quit;

    static UIButton* btn_load;
    static UIButton* btn_erase;

    static UIInputField* input_worldName;
};
