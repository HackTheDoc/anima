#include "include/Game/Components/QuestSystem.h"

#include "include/Game/Game.h"

#include "include/Text.h"

Quest::Quest() : id(ID::UNKNOWN) {}

Quest::Quest(const ID id) : id(id) {}

void Quest::tryFinish() {
    if (!isFinished()) return;

    const QuestTemplate q = Text::GetQuest(id);
    UI::AddPopUp(Text::Get("QUEST ") + q.title + Text::Get(" FINISHED"), false);

    /// TODO: handle rewards

    if (const auto& n = next())
        id = n.value();
}

/// TODO: keep it updated !!
bool Quest::isFinished() {
    switch (id) {
    case ID::AN_INMATE:
        return Game::island->getName() != "lost temple";

    case ID::UNKNOWN:
    case ID::COMING_SOON:
    default:
        return false;
    }
}

std::optional<Quest::ID> Quest::next() {
    switch (id) {
    case ID::AN_INMATE:
        return ID::COMING_SOON;
    case ID::UNKNOWN:
    case ID::COMING_SOON:
    default:
        return {};
    }
}

QuestSystem::QuestSystem(const Quest::ID curr_main) {
    sideQuests = {};
    currentSideQuest = -1;
    mainQuest.id = curr_main;
}

QuestSystem::~QuestSystem() {
    sideQuests.clear();
}

void QuestSystem::addQuest(const Quest::ID t) {
    Quest q{ t };
    sideQuests.push_back(q);
    currentSideQuest++;
}

void QuestSystem::update() {
    mainQuest.tryFinish();

    for (size_t i = 0; i < sideQuests.size(); i++)
        sideQuests[i].tryFinish();
}
