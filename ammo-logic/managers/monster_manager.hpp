#ifndef _MONSTER_MANAGER_HPP
#define _MONSTER_MANAGER_HPP 1

#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "map_manager.hpp"
#include "types.hpp"

class MonsterManager
{
public:
    MonsterManager(MapManager& map_manager);

    void Initialize(Client& client);

    void Get_Monster_List(std::vector<std::string>& monsters);

    int Get_Monster_Hp(const char* monster);
    std::array<int, 4> Get_Monster_Attack(const char* monster);
    std::array<int, 4> Get_Monster_Resistance(const char* monster);

    const MapCoord* Get_Monster_Coord(const char* monster) const;
    void Get_Monster_Loot(const char* monster, std::vector<Loot>& loot) const;

private:
    std::map<std::string, nlohmann::json> m_Monsters;
    std::map<std::string, std::vector<Loot>> m_Monsters_Loot;
    MapManager& m_Map_Manager;
};

#endif  // _MONSTER_MANAGER_HPP
