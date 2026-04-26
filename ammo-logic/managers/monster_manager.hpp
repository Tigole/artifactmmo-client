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
    MonsterManager() = default;

public:
    static MonsterManager singleton;

    void Initialize(void);

    void Get_Monster_List(std::vector<std::string>& monsters);

    int Get_Monster_Level(const char* monster);
    int Get_Monster_Hp(const char* monster);
    std::array<int, 4> Get_Monster_Attack(const char* monster);
    std::array<int, 4> Get_Monster_Resistance(const char* monster);
    int Get_Monster_Initiative(const char* monster);
    int Get_Monster_Critical_Strike(const char* monster);

    const MapCoord* Get_Monster_Coord(const char* monster) const;
    void Get_Monster_Loot(const char* monster, std::vector<Loot>& loot) const;

private:
    std::map<std::string, nlohmann::json> m_Monsters;
    std::map<std::string, std::vector<Loot>> m_Monsters_Loot;
};

#endif  // _MONSTER_MANAGER_HPP
