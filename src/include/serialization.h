#pragma once

#include <map>
#include <fstream>

struct ConfigStruct;

namespace serialize {

    template <typename K, typename V>
    void map(std::ofstream& outfile, const std::map<K, V>& map);

    template<typename T1, typename T2>
    void pair(std::ofstream& outfile, const std::pair<T1, T2>& pair);

    void config(const ConfigStruct& config);

}; // namepsace serialitation

namespace deserialize {

    template <typename K, typename V>
    void map(std::ifstream& infile, std::map<K, V>& map);

    template<typename T1, typename T2>
    void pair(std::ifstream& infile, const std::pair<T1, T2>& pair);

    ConfigStruct config();

}; // namespace deserialize
