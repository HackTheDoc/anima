#pragma once

#include "WindowState.h"

#include "../GifTexture.h"

#include "../UI/UIElements.h"

class PlayMenu : public WindowState {
public:
    PlayMenu();
    ~PlayMenu();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;

    /// @brief check if the state of the current selection
    /// @return true if activate else false
    static bool IsSelectionActived();

    /// @brief remove the informations about a world (useful when erasing a save)
    /// @param wid id of the world to remove info to
    static void RemoveInfos(int wid);

    /// @brief id of the selected world (1-4)
    static int Selection;

    static void OpenWorldNameInput();
    static void CloseWorldNameInput();

    /// @brief push the name from the input field to Game::WorldName variable
    static void ValidWorldName();
    
private:
    GifTexture *background;

    UILabel* title;

    static UIGameSaveButton* button[4];

    UIButton* quitButton;

    static UIButton* loadButton;
    static UIButton* eraseButton;

    /// @brief input field for the name of the world
    static UIInputField* worldNameInput;
};
