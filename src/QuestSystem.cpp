#include "include/Game/Components/QuestSystem.h"

#include "include/Text.h"

void Quest::load(const std::string& t) {
    QuestTemplate q = Text::GetQuest(t);

    title = q.title;
    content = q.content;
    next = q.next;
}

void Quest::finish() {
    if (!next.has_value()) return;

    load(next.value());
}

void Quest::isFinished() {
    /// TODO:
}

QuestSystem::QuestSystem(const std::string& curr_main) {
    others = {};
    curr_other = -1;

    main.load(curr_main);
}

QuestSystem::~QuestSystem() {
    others.clear();
}

void QuestSystem::addQuest(const std::string& t) {
    Quest q;
    q.load(t);
    others.push_back(q);
    curr_other++;
}
