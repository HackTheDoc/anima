#include "include/Game/Components/QuestSystem.h"

#include "include/Game/Game.h"

Quest::Quest() : id(ID::UNKNOWN) {}

Quest::Quest(const ID id) : id(id) {}

void Quest::try_finish() {
    if (!is_finished()) return;

    const QuestTemplate q = Text::GetQuest(id);
    UI::AddPopUp(Text::Get("QUEST ") +q.title+ Text::Get(" FINISHED"), false);

    /// TODO: handle rewards

    if (const auto& n = next())
        id = n.value();
}

/// TODO: keep it updated !!
bool Quest::is_finished() {
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
    others = {};
    curr_other = -1;
    main.id = curr_main;
}

QuestSystem::~QuestSystem() {
    others.clear();
}

void QuestSystem::addQuest(const Quest::ID t) {
    Quest q{t};
    others.push_back(q);
    curr_other++;
}

void QuestSystem::update() {
    main.try_finish();

    for (size_t i = 0; i < others.size(); i++)
        others[i].try_finish();
}
