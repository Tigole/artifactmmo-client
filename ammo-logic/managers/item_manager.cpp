#include "item_manager.hpp"

#include "keywords.hpp"
#include "managers/monster_manager.hpp"
#include "net/client.hpp"

ItemManager ItemManager::singleton;

void ItemManager::Initialize()
{
    Client::singleton.Get_Items(m_Items);
    Initialize_Recipes();
}

void ItemManager::Initialize_Recipes()
{
    m_Recipes.clear();
    for (auto& i: m_Items)
    {
        if (i.second["craft"].is_null() == false)
        {
            Recipe r;
            r.target_item = i.first;
            r.skill_name  = i.second["craft"]["skill"].get<std::string>();
            r.skill_level = i.second["craft"]["level"].get<int>();
            for (auto it = i.second["craft"]["items"].begin(); it != i.second["craft"]["items"].end(); it++)
            {
                r.required_items.push_back({ (*it)["code"].get<std::string>(), (*it)["quantity"].get<int>() });
            }
            m_Recipes.emplace(i.first, r);
        }
        if (i.second["type"] == "resource")
        {
            const std::string subtype = i.second["subtype"];
            if (subtype == Keywords::Skills::mining || subtype == Keywords::Skills::woodcutting || subtype == Keywords::Skills::fishing ||
                subtype == Keywords::Skills::alchemy)
            {
                GatheringRequirement gr;
                gr.skill_name  = subtype;
                gr.skill_level = i.second["level"];
                m_Gathering.emplace(i.first, gr);
            }
        }
        for (const auto& effect: i.second["effects"])
        {
            m_Effetcs[i.first][effect["code"]] = effect["value"].get<int>();
        }
        m_Levels[i.first] = i.second["level"];
        for (const auto& condition: i.second["conditions"])
        {
            printf("%s\n", condition.dump().c_str());
            m_Required_Levels[i.first] = condition["value"].get<int>();
        }
    }

    /// Loot
    {
        std::vector<std::string> l_Monster_List;
        MonsterManager::singleton.Get_Monster_List(l_Monster_List);

        std::vector<Loot> l_Loot;
        for (std::size_t ii = 0; ii < l_Monster_List.size(); ii++)
        {
            MonsterManager::singleton.Get_Monster_Loot(l_Monster_List[ii].c_str(), l_Loot);
            for (std::size_t jj = 0; jj < l_Loot.size(); jj++)
            {
                m_Looting[l_Loot[jj].code].push_back(l_Monster_List[ii]);
            }
        }
    }
}

void ItemManager::Get_Weapons(std::map<std::string, int>& weapons) const
{
    const std::array<const char*, 4> l_Attack_Names = {
        { "attack_fire", "attack_water", "attack_earth", "attack_air" }
    };

    for (auto& i: m_Items)
    {
        const std::string l_Type = i.second["type"].get<std::string>();
        if (l_Type == "weapon")
        {
            int l_Attack = 0;
            for (auto it = i.second["effects"].begin(); it != i.second["effects"].end(); it++)
            {
                for (auto a: l_Attack_Names)
                {
                    if ((*it)["code"].get<std::string>() == a)
                    {
                        l_Attack += (*it)["value"].get<int>();
                    }
                }
            }
            weapons.emplace(i.first, l_Attack);
        }
    }
}

void ItemManager::Get_Items(std::vector<std::string>& items) const
{
    items.clear();
    for (auto& i: m_Items)
    {
        items.push_back(i.first);
    }
}

bool ItemManager::Is_Weapon(const char* item_code) const
{
    auto it = m_Items.find(item_code);
    if (it != m_Items.end())
    {
        return it->second["type"] == "weapon";
    }
    return false;
}

std::array<int, 4> ItemManager::Get_Weapon_Attack(const char* item_code) const
{
    return {
        { Get_Effect_Value(item_code, "attack_fire"), Get_Effect_Value(item_code, "attack_water"),
         Get_Effect_Value(item_code, "attack_earth"), Get_Effect_Value(item_code, "attack_air") }
    };
}

std::array<int, 4> ItemManager::Get_Armor_Resistance(const char* item_code) const
{
    return {
        { Get_Effect_Value(item_code, "res_fire"), Get_Effect_Value(item_code, "res_water"), Get_Effect_Value(item_code, "res_earth"),
         Get_Effect_Value(item_code, "res_air") }
    };
}

std::array<int, 4> ItemManager::Get_Armor_Damage(const char* item_code) const
{
    return {
        { Get_Effect_Value(item_code, "dmg_fire"), Get_Effect_Value(item_code, "dmg_water"), Get_Effect_Value(item_code, "dmg_earth"),
         Get_Effect_Value(item_code, "dmg_air") }
    };
}

int ItemManager::Get_Armor_Hp(const char* item_code) const
{
    return Get_Effect_Value(item_code, "hp");
}

int ItemManager::Get_Required_Level(const char* item_code) const
{
    auto it = m_Required_Levels.find(item_code);
    if (it != m_Required_Levels.end())
    {
        return it->second;
    }
    return 0;
}

int ItemManager::Get_Item_Level(const char* item_code) const
{
    auto it = m_Levels.find(item_code);
    if (it != m_Levels.end())
    {
        return it->second;
    }
    return 0;
}

bool ItemManager::Is_Type(const char* item_code, const char* item_type) const
{
    auto it = m_Items.find(item_code);
    if (it != m_Items.end())
    {
        return it->second["type"].get<std::string>() == item_type;
    }
    return false;
}

int ItemManager::Get_Effect_Value(const char* item_code, const char* effect_code) const
{
    auto it = m_Effetcs.find(item_code);
    if (it != m_Effetcs.end())
    {
        auto effect_it = it->second.find(effect_code);
        if (effect_it != it->second.end())
        {
            return effect_it->second;
        }
    }
    return 0;
}

const Recipe* ItemManager::Get_Recipe(const char* item_code) const
{
    auto it = m_Recipes.find(item_code);
    if (it != m_Recipes.end())
    {
        return &it->second;
    }
    return nullptr;
}

const GatheringRequirement* ItemManager::Get_Gathering_Skill(const char* item_code) const
{
    auto it = m_Gathering.find(item_code);
    if (it != m_Gathering.end())
    {
        return &it->second;
    }
    return nullptr;
}

const char* ItemManager::Get_Loot_Monster_Name(const char* item_code) const
{
    auto it = m_Looting.find(item_code);
    if (it != m_Looting.end())
    {
        std::size_t idx = 0;
        return it->second[idx].c_str();
    }
    return nullptr;
}
