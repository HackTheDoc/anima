#pragma once

#include <string>
#include <vector>
#include <optional>

struct Quest {
    std::string title{ "UNKNOWN" };
    std::string content{ "" };
    std::optional<std::string> next{};

    void load(const std::string& t);
    void finish();
    void isFinished();
};

class QuestSystem {
public:
    Quest main;
    /// @brief side quests
    std::vector<Quest> others;
    size_t curr_other;

    QuestSystem(const std::string& curr_main);
    ~QuestSystem();

    void addQuest(const std::string& t);
};
