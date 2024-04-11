#pragma once

#include <vector>

#include "../../UI/UIElements.h"

class NPC;

struct Answer {
    enum State : bool {
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

    Answer(const std::string& text, const Type result, const std::string& id) {
        label[State::UNSELECTED] = new UILabel(text, "default", hue::white);
        label[State::SELECTED] = new UILabel(text, "default bold", hue::yellow);
        this->result = result;
        this->id = id;
    }
};

class Dialog : public UIElement {
public:
    Dialog(NPC* master, const std::string& id);
    ~Dialog();

    void draw() override;
    void destroy() override;

    void loadData();
    void setTextBox(const std::string& text);
    void addAnswer(const std::string& text, const Answer::Type result, const std::string& id, const int y, const int leftSpand);
    void validateAnswer();
    void moveCursorUp();
    void moveCursorDown();

private:
    std::string id;

    UIDialogBox* box;
    
    std::vector<Answer*> answers;
    int currentAnswer;

    NPC* master;
};
