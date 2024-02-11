#include "include/serialization.h"

#include "include/Save.h"

namespace serialize {
    template <typename K, typename V>
    void map(std::ofstream& outfile, const std::map<K, V>& map) {
        size_t msize = map.size();
        outfile.write(reinterpret_cast<const char*>(&msize), sizeof(size_t));
        for (const auto& [key, value] : map) {
            size_t ksize = key.size();
            outfile.write(reinterpret_cast<const char*>(&ksize), sizeof(size_t));
            outfile.write(key.data(), ksize);
            outfile.write(reinterpret_cast<const char*>(&value), sizeof(V));
        }
    }

    template<typename T1, typename T2>
    void pair(std::ofstream& outfile, const std::pair<T1, T2>& pair) {
        size_t fsize = pair.first.size();
        outfile.write(reinterpret_cast<const char*>(&fsize), sizeof(size_t));
        outfile.write(pair.first.data(), fsize);

        size_t ssize = pair.second.size();
        outfile.write(reinterpret_cast<const char*>(&ssize), sizeof(size_t));
        outfile.write(pair.second.data(), ssize);
    }


    void config(const ConfigStruct& config) {
        std::ofstream outfile("config", std::ios::binary);

        outfile.write(reinterpret_cast<const char*>(&config.autosave), sizeof(bool));
        outfile.write(reinterpret_cast<const char*>(&config.tutorial), sizeof(bool));

        outfile.write(reinterpret_cast<const char*>(&config.language), sizeof(Uint8));
        outfile.write(reinterpret_cast<const char*>(&config.window_mode), sizeof(Uint32));

        for (const auto& p : config.worlds)
            pair(outfile, p);

        map(outfile, config.controls);

        outfile.close();
    }

}; // namespace serialize

namespace deserialize {
    template <typename K, typename V>
    void map(std::ifstream& infile, std::map<K, V>& map) {
        size_t msize;
        infile.read(reinterpret_cast<char*>(&msize), sizeof(size_t));
        for (size_t i = 0; i < msize; ++i) {
            size_t ksize;
            infile.read(reinterpret_cast<char*>(&ksize), sizeof(size_t));
            std::string key(ksize, '\0');
            infile.read(&key[0], ksize);
            V value;
            infile.read(reinterpret_cast<char*>(&value), sizeof(V));
            map[key] = value;
        }
    }

    template<typename T1, typename T2>
    void pair(std::ifstream& infile, std::pair<T1, T2>& pair) {
        size_t fsize;
        infile.read(reinterpret_cast<char*>(&fsize), sizeof(size_t));
        std::string firstData(fsize, '\0');
        infile.read(&firstData[0], fsize);
        pair.first = std::move(firstData);

        size_t ssize;
        infile.read(reinterpret_cast<char*>(&ssize), sizeof(size_t));
        std::string secondData(ssize, '\0');
        infile.read(&secondData[0], ssize);
        pair.second = std::move(secondData);
    }

    ConfigStruct config() {
        ConfigStruct cstruct;

        std::ifstream infile("config", std::ios::binary);

        infile.read(reinterpret_cast<char*>(&cstruct.autosave), sizeof(bool));
        infile.read(reinterpret_cast<char*>(&cstruct.tutorial), sizeof(bool));

        infile.read(reinterpret_cast<char*>(&cstruct.language), sizeof(Uint8));
        infile.read(reinterpret_cast<char*>(&cstruct.window_mode), sizeof(Uint32));

        for (auto& p : cstruct.worlds)
            pair(infile, p);

        map(infile, cstruct.controls);

        infile.close();

        return cstruct;
    }

}; // namepsace deserialize
