#pragma once

#include <vector>

#include "../../UI/UIElements.h"

class NPC;

struct Answer {
    enum State {
        UNSELECTED,
        SELECTED
    };

    enum Type {
        CLOSE_DIALOG,
        OPEN_NEW_DIALOG
    };

    UILabel* label[2];
    Type result;
    std::string id;

    Answer() {}

    Answer(std::string text, Answer::Type result, std::string id) {
        label[State::UNSELECTED] = new UILabel(text, "default", hue::white);
        label[State::SELECTED] = new UILabel(text, "default bold", hue::yellow);
        this->result = result;
        this->id = id;
    }
};

class Dialog : public UIElement {
public:
    Dialog(NPC* master, std::string id);
    ~Dialog();

    void draw() override;
    void destroy() override;

    void loadData();
    void setTextBox(std::string text);
    void addAnswer(std::string text, Answer::Type result, std::string id, int y);
    void validateAnswer();
    void moveCursorUp();
    void moveCursorDown();

private:
    std::string id;

    UIDialogBox* box;
    std::vector<Answer*> answers;

    NPC* master;
    int currentAnswer;
};
