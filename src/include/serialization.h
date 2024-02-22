#pragma once

#include <fstream>
#include <filesystem>

#include "struct.h"

namespace fs = std::filesystem;

namespace serialize {

    template <typename K, typename V>
    void map(std::ofstream& outfile, const std::map<K, V>& map);

    template <typename T>
    void vector(std::ofstream& outfile, const std::vector<T>& vec);

    template <typename T1, typename T2>
    void pair(std::ofstream& outfile, const std::pair<T1, T2>& pair);

    template <typename T>
    void var(std::ofstream& outfile, const T& var);

    void vector2D(std::ofstream& outfile, const Vector2D& vec);

    void string(std::ofstream& outfile, const std::string& s);

    void teleporter(std::ofstream& outfile, const Struct::Teleporter& teleporter);
    void imap(std::ofstream& outfile, const Struct::Map& map);

    void item(std::ofstream& outfile, const Struct::Item& item);
    void inventory(std::ofstream& outfile, const Struct::Inventory& inv);

    void npc(std::ofstream& outfile, const Struct::NPC& npc);
    void doll(std::ofstream& outfile, const Struct::Doll& doll);
    void dead_body(std::ofstream& outfile, const Struct::DeadBody& body);
    void entity(std::ofstream& outfile, const Struct::Entity& entity);


    void island(std::ofstream& outfile, const Struct::Island& island);

    void player(std::ofstream& outfile, const Struct::Player& player);

    void game(const Struct::Game& game, fs::path path);

    void config(const Struct::Config& config);
}; // namepsace serialitation

namespace deserialize {

    template <typename K, typename V>
    void map(std::ifstream& infile, std::map<K, V>& map);

    template <typename T>
    void vector(std::ifstream& infile, std::vector<T>& vec);

    template<typename T1, typename T2>
    void pair(std::ifstream& infile, std::pair<T1, T2>& pair);

    template <typename T>
    void var(std::ifstream& infile, T& var);

    void vector2D(std::ifstream& infile, Vector2D& vec);

    void string(std::ifstream& infile, std::string& s);

    void inventory(std::ifstream& infile, Inventory& inv);

    void teleporter(std::ifstream& infile, Struct::Teleporter& teleporter);

    void item(std::ifstream& infile, Struct::Item& item);

    void npc(std::ifstream& infile, Struct::NPC& item);
    void doll(std::ifstream& infile, Struct::Doll& doll);
    void dead_body(std::ifstream& infile, Struct::DeadBody& body);
    void entity(std::ifstream& infile, Struct::Entity& entity);

    void island(std::ifstream& infile, Struct::Island& island);

    void player(std::ifstream& infile, Struct::Player& player);

    void game(Struct::Game& game, fs::path path);

    Struct::Config config();

}; // namespace deserialize
