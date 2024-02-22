#pragma once

#include <string>
#include <vector>
#include <optional>

struct Quest {
    enum ID {
        UNKNOWN,
        COMING_SOON,

        AN_INMATE
    };
    ID id;

    Quest();
    Quest(const ID id);

    void try_finish();
    bool is_finished();
    std::optional<ID> next();
};

class QuestSystem {
public:
    Quest main;
    /// @brief side quests
    std::vector<Quest> others;
    size_t curr_other;

    QuestSystem(const Quest::ID curr_main);
    ~QuestSystem();

    void addQuest(const Quest::ID t);

    void update();
};
