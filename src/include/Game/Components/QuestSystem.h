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

    void tryFinish();
    bool isFinished();
    std::optional<ID> next();
};

class QuestSystem {
public:
    Quest mainQuest;
    std::vector<Quest> sideQuests;
    size_t currentSideQuest;

    QuestSystem(const Quest::ID curr_main);
    ~QuestSystem();

    void addQuest(const Quest::ID t);

    void update();
};
