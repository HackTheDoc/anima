#pragma once

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

/// @brief structure of an answer (used in DialogTemplate)
struct AnswerTemplate {
    std::string text;
    int result;
    std::string id;
    int ypos;
};

/// @brief structure containing the infos of a dialog
struct DialogTemplate {
    std::string text;
    std::vector<AnswerTemplate> answers;
    int result;
};

struct QuestTemplate {
    std::string title;
    std::string content;
};

enum Language : Uint8 {
    ENGLISH,
    FRENCH
};

class Text {
public:

    /// @brief parse a text in the current language of the window
    /// @param tag text to translate
    /// @return
    static std::string Get(const std::string& tag);

    /// @brief parse a dialog based on it's tag
    /// @param tag 
    /// @return structure containing the dialog's data
    static DialogTemplate GetDialog(const std::string& tag);

    /// @brief parse a quest details based on the quest's id
    /// @param qid 
    /// @return structure containing the quest details
    static QuestTemplate GetQuest(const int qid);

    static std::vector<std::string> GetCinematic(const std::string& tag);

private:
    /// @brief open the right translation file
    /// @return json structure with the translated texts
    static json OpenTranslation();
};
