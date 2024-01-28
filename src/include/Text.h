#pragma once

#include <vector>
#include <string>
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

class Text {
public:
    enum Language {
        ENGLISH,
        FRENCH
    };

    /// @brief parse a text
    /// @param tag text to translate
    /// @return translated text
    static std::string Get(std::string tag);

    /// @brief parse a dialog based on it's tag
    /// @param tag 
    /// @return structure containing the dialog's data
    static DialogTemplate GetDialog(std::string tag);

private:
    /// @brief open the right translation file
    /// @return json structure with the translated texts
    static json OpenTranslation();
};
