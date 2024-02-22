#include "include/serialization.h"

#include <iostream>

namespace serialize {
    template <typename K, typename V>
    void map(std::ofstream& outfile, const std::map<K, V>& map) {
        size_t msize = map.size();
        var(outfile, msize);

        for (const auto& [key, value] : map) {
            size_t ksize = key.size();
            outfile.write(reinterpret_cast<const char*>(&ksize), sizeof(size_t));
            outfile.write(key.data(), ksize);
            outfile.write(reinterpret_cast<const char*>(&value), sizeof(V));
        }
    }

    template <typename T>
    void vector(std::ofstream& outfile, const std::vector<T>& vec) {
        size_t size = vec.size();
        var(outfile, size);

        for (const auto& elt : vec)
            var(outfile, elt);
    }

    template<typename T1, typename T2>
    void pair(std::ofstream& outfile, const std::pair<T1, T2>& pair) {
        size_t fsize = pair.first.size();
        var(outfile, fsize);
        outfile.write(pair.first.data(), fsize);

        size_t ssize = pair.second.size();
        var(outfile, ssize);
        outfile.write(pair.second.data(), ssize);
    }

    template <typename T>
    void var(std::ofstream& outfile, const T& var) {
        outfile.write(reinterpret_cast<const char*>(&var), sizeof(T));
    }

    void vector2D(std::ofstream& outfile, const Vector2D& vec) {
        var(outfile, vec.x);
        var(outfile, vec.y);
    }

    void string(std::ofstream& outfile, const std::string& s) {
        size_t size = s.size();
        var(outfile, size);
        outfile.write(s.data(), size);
    }

    void teleporter(std::ofstream& outfile, const Struct::Teleporter& teleporter) {
        vector2D(outfile, teleporter.pos);
        string(outfile, teleporter.dest);
        vector2D(outfile, teleporter.dest_pos);
        var(outfile, teleporter.damage_level);
        var(outfile, teleporter.is_door);
    }

    void imap(std::ofstream& outfile, const Struct::Map& map) {
        var(outfile, map.width);
        var(outfile, map.height);

        size_t size = map.tiles.size();
        var(outfile, size);

        for (const auto& vec : map.tiles)
            vector(outfile, vec);
    }

    void item(std::ofstream& outfile, const Struct::Item& item) {
        vector2D(outfile, item.pos);
        var(outfile, item);
    };

    void inventory(std::ofstream& outfile, const Struct::Inventory& inv) {
        var(outfile, inv.capacity);

        size_t size = inv.items.size();
        var(outfile, size);

        for (const auto& i : inv.items)
            item(outfile, i);
    }

    void npc(std::ofstream& outfile, const Struct::NPC& npc) {
        var(outfile, Entity::Type::NON_PLAYER_CHARACTER);

        var(outfile, npc.species);
        var(outfile, npc.behavior);
        string(outfile, npc.name);
        var(outfile, npc.hp);
        vector2D(outfile, npc.pos);
        var(outfile, npc.hasdialog);
        inventory(outfile, npc.inventory);
    }

    void doll(std::ofstream& outfile, const Struct::Doll& doll) {
        var(outfile, Entity::Type::DOLL);

        vector2D(outfile, doll.pos);
        inventory(outfile, doll.inventory);
    }

    void dead_body(std::ofstream& outfile, const Struct::DeadBody& body) {
        var(outfile, Entity::Type::DEAD_BODY);

        var(outfile, body.species);
        vector2D(outfile, body.pos);
        inventory(outfile, body.inventory);
        var(outfile, body.o_type);
        var(outfile, body.o_behavior);
        string(outfile, body.o_name);
        var(outfile, body.o_hasdialog);
    }

    void entity(std::ofstream& outfile, const Struct::Entity& entity) {
        struct EntityVisitor {
            std::ofstream& outfile;

            void operator()(const Struct::NPC& npc) const {
                serialize::npc(outfile, npc);
            }

            void operator()(const Struct::Doll& doll) const {
                serialize::doll(outfile, doll);
            }

            void operator()(const Struct::DeadBody& body) const {
                serialize::dead_body(outfile, body);
            }
        };

        EntityVisitor visitor{ outfile };
        std::visit(visitor, entity.e);
    }

    void island(std::ofstream& outfile, const Struct::Island& island) {
        string(outfile, island.name);
        imap(outfile, island.map);

        size_t psize = island.portals.size();
        var(outfile, psize);
        for (const auto& p : island.portals)
            teleporter(outfile, p);

        size_t isize = island.items.size();
        var(outfile, isize);
        for (const auto& i : island.items)
            item(outfile, i);

        size_t esize = island.entities.size();
        var(outfile, esize);
        for (const auto& e : island.entities)
            entity(outfile, e);
    }

    void player(std::ofstream& outfile, const Struct::Player& player) {
        string(outfile, player.name);
        var(outfile, player.hp);
        var(outfile, player.numen_level);
        for (const auto& elt : player.power)
            var(outfile, elt);
        var(outfile, player.state);
        var(outfile, player.tutorial_step);
        var(outfile, player.curr_main_quest);
        vector(outfile, player.curr_other_quests);
        string(outfile, player.curr_island_on);
        vector2D(outfile, player.pos);

        var(outfile, player.is_controlling_an_entity);
        if (player.is_controlling_an_entity)
            entity(outfile, player.controlled_entity);
    }

    void game(const Struct::Game& game, fs::path path) {
        std::ofstream outfile(path, std::ios::binary);

        var(outfile, game.world_id);
        player(outfile, game.player);

        size_t size = game.islands.size();
        var(outfile, size);
        for (const auto& [key, value] : game.islands) {
            string(outfile, key);
            island(outfile, value);
        }

        outfile.close();
    }

    void config(const Struct::Config& config) {
        std::ofstream outfile("config", std::ios::binary);

        var(outfile, config.autosave);
        var(outfile, config.tutorial);

        var(outfile, config.language);
        var(outfile, config.window_mode);


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
        var(infile, msize);
        for (size_t i = 0; i < msize; ++i) {
            size_t ksize;
            var(infile, ksize);
            std::string key(ksize, '\0');
            infile.read(&key[0], ksize);
            V value;
            var(infile, value);
            map[key] = value;
        }
    }

    template <typename T>
    void vector(std::ifstream& infile, std::vector<T>& vec) {
        size_t size;
        var(infile, size);

        vec.resize(size);
        for (size_t i = 0; i < size; i++)
            var(infile, vec[i]);
    }

    template<typename T1, typename T2>
    void pair(std::ifstream& infile, std::pair<T1, T2>& pair) {
        size_t fsize;
        var(infile, fsize);
        std::string firstData(fsize, '\0');
        infile.read(&firstData[0], fsize);
        pair.first = std::move(firstData);

        size_t ssize;
        var(infile, ssize);
        std::string secondData(ssize, '\0');
        infile.read(&secondData[0], ssize);
        pair.second = std::move(secondData);
    }

    template <typename T>
    void var(std::ifstream& infile, T& var) {
        infile.read(reinterpret_cast<char*>(&var), sizeof(T));
    }

    void vector2D(std::ifstream& infile, Vector2D& vec) {
        var(infile, vec.x);
        var(infile, vec.y);
    }

    void string(std::ifstream& infile, std::string& s) {
        size_t size;
        var(infile, size);
        s.resize(size);
        infile.read(&s[0], size);
    }

    void teleporter(std::ifstream& infile, Struct::Teleporter& teleporter) {
        vector2D(infile, teleporter.pos);
        string(infile, teleporter.dest);
        vector2D(infile, teleporter.dest_pos);
        var(infile, teleporter.damage_level);
        var(infile, teleporter.is_door);
    }

    void imap(std::ifstream& infile, Struct::Map& map) {
        var(infile, map.width);
        var(infile, map.height);

        size_t size = map.tiles.size();
        var(infile, size);

        map.tiles.resize(size);
        for (size_t i = 0; i < size; i++)
            vector(infile, map.tiles[i]);
    }

    void item(std::ifstream& infile, Struct::Item& item) {
        vector2D(infile, item.pos);
        var(infile, item);
    };

    void inventory(std::ifstream& infile, Struct::Inventory& inv) {
        var(infile, inv.capacity);

        size_t size;
        var(infile, size);
        inv.items.resize(size);
        for (size_t i = 0; i < size; i++)
            item(infile, inv.items[i]);
    }

    void npc(std::ifstream& infile, Struct::NPC& npc) {
        var(infile, npc.species);
        var(infile, npc.behavior);
        string(infile, npc.name);
        var(infile, npc.hp);
        vector2D(infile, npc.pos);
        var(infile, npc.hasdialog);
        inventory(infile, npc.inventory);
    }

    void doll(std::ifstream& infile, Struct::Doll& doll) {
        vector2D(infile, doll.pos);
        inventory(infile, doll.inventory);
    }

    void dead_body(std::ifstream& infile, Struct::DeadBody& body) {
        var(infile, body.species);
        vector2D(infile, body.pos);
        inventory(infile, body.inventory);
        var(infile, body.o_type);
        var(infile, body.o_behavior);
        string(infile, body.o_name);
        var(infile, body.o_hasdialog);
    }

    void entity(std::ifstream& infile, Struct::Entity& entity) {
        EntityType t;
        var(infile, t);

        switch (t) {
        case EntityType::NON_PLAYER_CHARACTER:
            entity.e = Struct::NPC{};
            break;
        case EntityType::DOLL:
            entity.e = Struct::Doll{};
            break;
        case EntityType::DEAD_BODY:
            entity.e = Struct::DeadBody{};
            break;
        default:
            break;
        }

        struct Visitor {
            std::ifstream& infile;

            void operator()(Struct::NPC& npc) const {
                deserialize::npc(infile, npc);
            }

            void operator()(Struct::Doll& doll) const {
                deserialize::doll(infile, doll);
            }

            void operator()(Struct::DeadBody& body) const {
                deserialize::dead_body(infile, body);
            }
        };

        Visitor visitor{ infile };
        std::visit(visitor, entity.e);
    }

    void island(std::ifstream& infile, Struct::Island& island) {
        string(infile, island.name);
        imap(infile, island.map);

        size_t psize;
        var(infile, psize);
        island.portals.resize(psize);
        for (size_t i = 0; i < psize; i++)
            teleporter(infile, island.portals[i]);

        size_t isize;
        var(infile, isize);
        island.items.resize(isize);
        for (size_t i = 0; i < isize; i++)
            item(infile, island.items[i]);

        size_t esize;
        var(infile, esize);
        island.entities.resize(esize);
        for (size_t i = 0; i < esize; i++)
            entity(infile, island.entities[i]);
    }

    void player(std::ifstream& infile, Struct::Player& player) {
        string(infile, player.name);
        var(infile, player.hp);
        var(infile, player.numen_level);
        for (auto& elt : player.power)
            var(infile, elt);

        var(infile, player.state);
        var(infile, player.tutorial_step);

        var(infile, player.curr_main_quest);
        vector(infile, player.curr_other_quests);

        string(infile, player.curr_island_on);
        vector2D(infile, player.pos);

        var(infile, player.is_controlling_an_entity);
        if (player.is_controlling_an_entity)
            entity(infile, player.controlled_entity);
    }

    void game(Struct::Game& game, fs::path path) {
        std::ifstream infile(path, std::ios::binary);

        var(infile, game.world_id);
        player(infile, game.player);

        size_t size;
        var(infile, size);
        for (size_t i = 0; i < size; ++i) {
            std::string key;
            string(infile, key);

            game.islands[key] = Struct::Island{};
            island(infile, game.islands[key]);
        }

        infile.close();
    }

    Struct::Config config() {
        Struct::Config cstruct;

        std::ifstream infile("config", std::ios::binary);

        var(infile, cstruct.autosave);
        var(infile, cstruct.tutorial);

        var(infile, cstruct.language);
        var(infile, cstruct.window_mode);

        for (auto& p : cstruct.worlds)
            pair(infile, p);

        map(infile, cstruct.controls);

        infile.close();

        return cstruct;
    }

}; // namepsace deserialize
