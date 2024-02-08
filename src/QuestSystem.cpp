#include "include/Game/Components/QuestSystem.h"

Quest::Quest() : id(ID::UNKNOWN) {}

Quest::Quest(const ID id) : id(id) {}

void Quest::finish() {
    if (const auto& n = next())
        id = n.value();
}

void Quest::isFinished() {
    /// TODO:
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
