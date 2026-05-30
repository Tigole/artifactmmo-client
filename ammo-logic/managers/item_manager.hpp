#ifndef _ITEM_MANAGER_HPP
#define _ITEM_MANAGER_HPP 1

#include <map>
#include <nlohmann/json.hpp>
#include <string>

#include "types.hpp"

class Client;
class MonsterManager;

struct ItemEffect
{
    std::string code;
    int value;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ItemEffect, code, value);
};

class ItemManager
{
    ItemManager() = default;

public:
    static ItemManager singleton;

    void Initialize(void);

    void Get_Weapons(std::map<std::string, int>& weapons) const;
    void Get_Items(std::vector<std::string>& items) const;

    bool Is_Weapon(const char* item_code) const;
    std::array<int, 4> Get_Weapon_Attack(const char* item_code) const;
    std::array<int, 4> Get_Armor_Resistance(const char* item_code) const;
    std::array<int, 4> Get_Armor_Damage(const char* item_code) const;
    int Get_Armor_Hp(const char* item_code) const;
    int Get_Required_Level(const char* item_code) const;
    int Get_Item_Effect_Prospecting(const char* item_code) const;

    int Get_Item_Level(const char* item_code) const;

    bool Is_Type(const char* item_code, const char* item_type) const;

    const Recipe* Get_Recipe(const char* item_code) const;
    const GatheringRequirement* Get_Gathering_Skill(const char* item_code) const;
    const char* Get_Loot_Monster_Name(const char* item_code) const;

private:
    std::map<std::string, nlohmann::json> m_Items;
    std::map<std::string, Recipe> m_Recipes;
    std::map<std::string, GatheringRequirement> m_Gathering;
    std::map<std::string, std::vector<std::string>> m_Looting;
    std::map<std::string, std::map<std::string, int>> m_Effetcs;
    std::map<std::string, int> m_Levels;
    std::map<std::string, int> m_Required_Levels;

    void Initialize_Recipes(void);
    int Get_Effect_Value(const char* item_code, const char* effect_code) const;
};

#endif  // _ITEM_MANAGER_HPP
