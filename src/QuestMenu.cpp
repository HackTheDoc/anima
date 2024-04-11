#include "include/WindowStates/QuestMenu.h"

#include "include/Text.h"
#include "include/Window.h"

#include "include/Game/Entities/Player.h"

QuestMenu::QuestMenu() {}

QuestMenu::~QuestMenu() {}

void QuestMenu::init() {
    container.h = 4 * Window::screen.h / 5;
    container.y = (Window::screen.h - container.h) / 2;

    container.w = 4 * Window::screen.w / 5;
    container.x = (Window::screen.w - container.w) / 2;

    lbl_title = new UILabel(Text::Get("Quests"), "h3", hue::font);
    lbl_title->place(
        container.x + (container.w - lbl_title->width()) / 2,
        container.y + 8 * (Window::fullscreen + 1)
    );

    const int mlength = container.w - 8 * (Window::fullscreen + 1);

    const QuestTemplate mqt = Text::GetQuest(Player::quest->mainQuest.id);
    lbl_mainQuestTitle = new UILabel(mqt.title, "h4", hue::font, mlength);
    lbl_mainQuestContent = new UILabel(mqt.content, "big", hue::font, mlength, true);

    const int yoff = (container.h + lbl_title->y() + lbl_title->height() + 4 * (Window::fullscreen + 1)) / 2;
    const int h = lbl_mainQuestTitle->height() + lbl_mainQuestContent->height() + 4 * (Window::fullscreen + 1);

    lbl_mainQuestTitle->place(
        container.x + (container.w - lbl_mainQuestTitle->width()) / 2,
        yoff - h / 2
    );

    lbl_mainQuestContent->place(
        container.x + (container.w - lbl_mainQuestContent->width()) / 2,
        lbl_mainQuestTitle->y() + lbl_mainQuestTitle->height() + 4 * (Window::fullscreen + 1)
    );
}

void QuestMenu::update() {

}

void QuestMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::blur);
    Manager::DrawFilledRect(&container, hue::ui_background);

    lbl_title->draw();

    Manager::DrawLine(
        container.x,
        lbl_title->y() + lbl_title->height() + 4 * (Window::fullscreen + 1),
        container.x + container.w,
        lbl_title->y() + lbl_title->height() + 4 * (Window::fullscreen + 1),
        hue::border
    );

    lbl_mainQuestTitle->draw();
    lbl_mainQuestContent->draw();

    Manager::DrawRect(&container, hue::border);
}

void QuestMenu::clean() {
    lbl_title->destroy();

    lbl_mainQuestTitle->destroy();
    lbl_mainQuestContent->destroy();
}
