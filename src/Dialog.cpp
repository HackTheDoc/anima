#include "include/Game/Components/Dialog.h"

#include "include/Game/Game.h"
#include "include/Game/Entities/NPC.h"

#include "include/Text.h"

Dialog::Dialog(NPC* master, const std::string& id) {
    this->master = master;
    this->id = id;
    currentAnswer = 0;
    loadData();
}

Dialog::~Dialog() {}

void Dialog::draw() {
    box->draw();
    for (int i = 0; i < (int)answers.size(); i++) {
        Answer* a = answers[i];
        if (i == currentAnswer) a->label[Answer::State::SELECTED]->draw();
        else a->label[Answer::State::UNSELECTED]->draw();
    }
}

void Dialog::destroy() {
    box->destroy();
    for (Answer* a : answers) {
        a->label[Answer::State::UNSELECTED]->destroy();
        a->label[Answer::State::SELECTED]->destroy();
    }
    answers.clear();
}

void Dialog::loadData() {
    DialogTemplate d = Text::GetDialog(id);

    setTextBox(d.text);

    const int x = box->x();
    const int y = box->y();
    for (AnswerTemplate a : d.answers) {
        addAnswer(
            a.text,
            (Answer::Type)a.result,
            a.id,
            y - a.ypos,
            x
        );
    }
}

void Dialog::setTextBox(const std::string& text) {
    box = new UIDialogBox(master->name, text);
    box->place();
}

void Dialog::addAnswer(const std::string& text, const Answer::Type result, const std::string& id, const int y, const int leftSpan) {
    Answer* a = new Answer(text, result, id);
    a->label[Answer::State::UNSELECTED]->placeLeft(y, leftSpan);
    a->label[Answer::State::SELECTED]->placeLeft(y, leftSpan);
    answers.push_back(a);
}

void Dialog::validateAnswer() {
    if (answers.size() == 0) {
        master->closeDialog();
        return;
    }

    Answer* a = answers[currentAnswer];
    switch (a->result) {
    case Answer::Type::CLOSE_DIALOG:
        master->closeDialog();
        break;
    case Answer::Type::OPEN_NEW_DIALOG:
        master->setDialog(a->id);
        break;
    default:
        break;
    }
}

void Dialog::moveCursorUp() {
    currentAnswer++;
    if (currentAnswer >= (int)answers.size())
        currentAnswer = 0;
}

void Dialog::moveCursorDown() {
    currentAnswer--;
    if (currentAnswer < 0)
        currentAnswer = (int)answers.size() - 1;
}
