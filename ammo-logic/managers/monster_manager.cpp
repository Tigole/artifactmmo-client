#include "monster_manager.hpp"

#include "net/client.hpp"

MonsterManager MonsterManager::singleton;

void MonsterManager::Initialize(void)
{
    Client::singleton.Get_Monsters(m_Monsters);
    for (auto m: m_Monsters)
    {
        for (auto l: m.second["drops"])
        {
            m_Monsters_Loot[m.first].push_back(l.get<Loot>());
        }
    }
}

void MonsterManager::Get_Monster_List(std::vector<std::string>& monsters)
{
    monsters.clear();
    monsters.reserve(m_Monsters.size());
    for (auto& m: m_Monsters)
    {
        monsters.push_back(m.first);
    }

    std::sort(monsters.begin(), monsters.end(), [this](const std::string& left, const std::string& right)
    { return m_Monsters[left]["level"].get<int>() > m_Monsters[right]["level"].get<int>(); });
}

int MonsterManager::Get_Monster_Hp(const char* monster)
{
    return m_Monsters[monster]["hp"].get<int>();
}

std::array<int, 4> MonsterManager::Get_Monster_Attack(const char* monster)
{
    return {
        { m_Monsters[monster]["attack_fire"].get<int>(), m_Monsters[monster]["attack_water"].get<int>(),
         m_Monsters[monster]["attack_earth"].get<int>(), m_Monsters[monster]["attack_air"].get<int>() }
    };
}

std::array<int, 4> MonsterManager::Get_Monster_Resistance(const char* monster)
{
    return {
        { m_Monsters[monster]["res_fire"].get<int>(), m_Monsters[monster]["res_water"].get<int>(),
         m_Monsters[monster]["res_earth"].get<int>(), m_Monsters[monster]["res_air"].get<int>() }
    };
}

const MapCoord* MonsterManager::Get_Monster_Coord(const char* monster) const
{
    return MapManager::singleton.Get_Monster_Coord(monster);
}

void MonsterManager::Get_Monster_Loot(const char* monster, std::vector<Loot>& loot) const
{
    auto m = m_Monsters_Loot.find(monster);
    loot.clear();
    if (m != m_Monsters_Loot.end())
    {
        loot = m->second;
    }
}
