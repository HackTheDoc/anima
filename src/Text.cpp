#include "include/Text.h"

#include "include/Window.h"

#include <fstream>

std::string Text::Get(std::string tag) {
    const json data = OpenTranslation();

    const std::string t = data[tag];

    return t;
}

DialogTemplate Text::GetDialog(std::string tag) {
    const json raw = OpenTranslation();

    const auto& data = raw["dialog"][tag];
    DialogTemplate d;

    d.text = data["text"];
    d.result = data["result"];

    int n = data["numberOfAnswers"];
    for (int i = 0; i < n; i++) {
        const auto& a = data[std::to_string(i)];
        d.answers.push_back({a[0], a[1], a[2], (32+16*Window::fullscreen)*(i+1)});
    }

    return d;
}

QuestTemplate Text::GetQuest(const int qid) {
    const json raw = OpenTranslation();

    const auto& data = raw["quest"][qid];
    QuestTemplate q;

    q.title = data["title"];
    q.content = data["content"];
    
    return q;
}

std::vector<std::string> Text::GetCinematic(const std::string& tag) {
    const json raw = OpenTranslation();

    const auto& data = raw["cinematics"];
    return data[tag];
}

json Text::OpenTranslation() {
    std::string path = "./data/translations/";

    switch (Window::language) {
    case Text::Language::ENGLISH:
        path += "english.json";
        break;
    case Text::Language::FRENCH:
        path += "french.json";
        break;
    default:
        break;
    }

    std::fstream infile(path);
    json data;
    infile >> data;
    infile.close();

    return data;
}
