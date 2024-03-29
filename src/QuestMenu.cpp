#include "include/WindowState/QuestMenu.h"

#include "include/Text.h"
#include "include/Window.h"
#include "include/Manager.h"

#include "include/Game/Entities/Player.h"

QuestMenu::QuestMenu() {}

QuestMenu::~QuestMenu() {}

void QuestMenu::init() {
    container.h = 4 * Window::screen.h / 5;
    container.y = (Window::screen.h - container.h) / 2;

    container.w = 4 * Window::screen.w / 5;
    container.x = (Window::screen.w - container.w) / 2;

    title = new UILabel(Text::Get("Quests"), "h3", hue::font);
    title->place(
        container.x + (container.w - title->width()) / 2,
        container.y + 8*(Window::fullscreen+1)
    );

    const int mlength = container.w-8*(Window::fullscreen+1);

    QuestTemplate mqt = Text::GetQuest(Player::quest->main.id);
    mainqt = new UILabel(mqt.title, "h4", hue::font, mlength);
    mainqc = new UILabel(mqt.content, "big", hue::font, mlength, true);

    const int yoff = (container.h + title->y() + title->height() + 4*(Window::fullscreen+1)) / 2;
    const int h = mainqt->height() + mainqc->height() + 4*(Window::fullscreen+1);

    mainqt->place(
        container.x + (container.w - mainqt->width()) / 2,
        yoff - h/2
    );

    mainqc->place(
        container.x + (container.w - mainqc->width()) / 2,
        mainqt->y() + mainqt->height() + 4*(Window::fullscreen+1)
    );
}

void QuestMenu::update() {

}

void QuestMenu::render() {
    Manager::DrawFilledRect(&Window::screen, hue::blur);
    Manager::DrawFilledRect(&container, hue::ui_background);

    title->draw();

    Manager::DrawLine(
        container.x,
        title->y() + title->height() + 4*(Window::fullscreen+1),
        container.x + container.w,
        title->y() + title->height() + 4*(Window::fullscreen+1),
        hue::border
    );

    mainqt->draw();
    mainqc->draw();

    Manager::DrawRect(&container, hue::border);
}

void QuestMenu::clean() {
    title->destroy();

    mainqt->destroy();
    mainqc->destroy();
}
