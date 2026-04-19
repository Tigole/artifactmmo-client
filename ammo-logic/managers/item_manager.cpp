#include "item_manager.hpp"

#include "keywords.hpp"
#include "managers/monster_manager.hpp"
#include "net/client.hpp"

ItemManager ItemManager::singleton;

void ItemManager::Initialize()
{
    Client::singleton.Get_Items(m_Items);
    for (auto& i: m_Items)
    {
        printf("item '%s'\n", i.first.c_str());
    }
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
        return it->second.begin()->c_str();
    }
    return nullptr;
}

#include "character/character.hpp"
#include "managers/inventory_manager.hpp"
#include "managers/item_manager.hpp"
#include "managers/npc_manager.hpp"
#include "managers/resource_manager.hpp"
#include "systems/fight_system.hpp"

ItemCraftingManager ItemCraftingManager::singleton;

void ItemCraftingManager::Initialize(void)
{
    m_Workshop_Coords[Keywords::Skills::mining]          = { 1, 5 };
    m_Workshop_Coords[Keywords::Skills::woodcutting]     = { -2, -3 };
    m_Workshop_Coords[Keywords::Skills::fishing]         = { 0, 0 };
    m_Workshop_Coords[Keywords::Skills::alchemy]         = { 2, 3 };
    m_Workshop_Coords[Keywords::Skills::weaponcrafting]  = { 2, 1 };
    m_Workshop_Coords[Keywords::Skills::gearcrafting]    = { 3, 1 };
    m_Workshop_Coords[Keywords::Skills::jewelrycrafting] = { 1, 3 };
    m_Workshop_Coords[Keywords::Skills::cooking]         = { 1, 1 };
}

void ItemCraftingManager::Make_Craft_Item(const System* sys, Character& character, const ItemOrder& item)
{
    Get_Item(sys, character, item);
}

void ItemCraftingManager::Make_Recycle_Item(const System* sys, Character& character, const ItemOrder& item)
{
    const Recipe* r = ItemManager::singleton.Get_Recipe(item.code.c_str());
    if (r != nullptr)
    {
        character.Add_Move(sys, m_Workshop_Coords[r->skill_name]);
        character.Add_Recycle_Item(sys, item);
    }
}

bool ItemCraftingManager::May_Craft(Character& character, const char* item_code) const
{
    const Recipe* r                = ItemManager::singleton.Get_Recipe(item_code);
    const GatheringRequirement* rg = ItemManager::singleton.Get_Gathering_Skill(item_code);
    const char* l_Monster_Name     = ItemManager::singleton.Get_Loot_Monster_Name(item_code);

    if (r != nullptr)
    {
        if (r->skill_level <= character.Get_Skill_Level(r->skill_name.c_str()))
        {
            bool may_craft = true;
            for (const ItemOrder& i: r->required_items)
            {
                const int inventory_count = character.Get_Item_Count(i.code.c_str());
                const int bank_count      = InventoryManager::singleton.Get_Bank_Item_Count(i.code.c_str());

                if (bank_count < i.quantity)
                {
                    may_craft = false;
                    printf("'%s' not enough '%s' for crafting '%s' (have %d required %d)\n", character.Get_Character(), i.code.c_str(),
                           item_code, bank_count, i.quantity);
                }
            }
            return may_craft;
        }
        return false;
    }
    else if (rg != nullptr)
    {
        return rg->skill_level <= character.Get_Skill_Level(rg->skill_name.c_str());
    }
    else if (l_Monster_Name != nullptr)
    {
        FightContext f;
        return FightSystem::singleton.MayWin(character, l_Monster_Name, f);
    }
    return false;
}

void ItemCraftingManager::Get_Item(const System* sys, Character& character, const ItemOrder& item)
{
    const Recipe* r                  = ItemManager::singleton.Get_Recipe(item.code.c_str());
    const int l_Bank_Item_Count      = InventoryManager::singleton.Get_Bank_Item_Count(item.code.c_str());
    const int l_Inventory_Item_Count = character.Get_Item_Count(item.code.c_str());

    if ((l_Inventory_Item_Count < item.quantity) && (l_Bank_Item_Count > 0))
    {
        const MapCoord Bank_Coord = InventoryManager::singleton.Get_Bank_Nearest_Coord(character);
        if (character.Should_Move(Bank_Coord))
        {
            character.Add_Move(sys, Bank_Coord);
        }
        else
        {
            const int l_Item_Count = item.quantity - l_Inventory_Item_Count;
            character.Add_Withdraw_Item(
                sys, { item.code, std::min(std::min(l_Item_Count, character.Get_Inventory_Remaining_Space()), l_Bank_Item_Count) });
        }
    }
    else if (r == nullptr)
    {
        const GatheringRequirement* rg = ItemManager::singleton.Get_Gathering_Skill(item.code.c_str());
        const char* l_Monster_Name     = ItemManager::singleton.Get_Loot_Monster_Name(item.code.c_str());
        const NPCItemTrade* t          = NPCManager::singleton.Get_Seller(item.code.c_str());

        if (l_Monster_Name != nullptr)
        {
            FightContext fight_context;
            if (FightSystem::singleton.MayWin(character, l_Monster_Name, fight_context) == true)
            {
                FightSystem::singleton.Fight_Against(sys, character, l_Monster_Name, fight_context);
                return;
            }
            else
            {
                throw std::runtime_error(fmt::format("can't win against '{}' for looting '{}'", l_Monster_Name, item.code));
            }
        }

        if (rg != nullptr)
        {
            if (character.Get_Skill_Level(rg->skill_name.c_str()) >= rg->skill_level)
            {
                const MapCoord* coord = ResourceManager::singleton.Get_Resource_Coord(character, item.code.c_str());
                if (coord != nullptr)
                {
                    const char* l_Weapon = nullptr;
                    if (rg->skill_name == Keywords::Skills::mining)
                    {
                        l_Weapon = Keywords::Items::Weapons::Tools::Pickaxes::copper_pickaxe;
                    }
                    else if (rg->skill_name == Keywords::Skills::woodcutting)
                    {
                        l_Weapon = Keywords::Items::Weapons::Tools::Axes::copper_axe;
                    }
                    else if (rg->skill_name == Keywords::Skills::fishing)
                    {
                        l_Weapon = Keywords::Items::Weapons::Tools::FishingRods::fishing_net;
                    }
                    else if (rg->skill_name == Keywords::Skills::alchemy)
                    {
                        l_Weapon = Keywords::Items::Weapons::Tools::Gloves::apprentice_gloves;
                    }
                    if (character.Get_Equiped_Weapon() != l_Weapon)
                    {
                        if (character.Get_Item_Count(l_Weapon) > 0)
                        {
                            if (character.Get_Equiped_Weapon().size() > 0)
                            {
                                // character.Add_Unequip_Item("weapon");
                            }
                            character.Add_Equip_Item(sys, "weapon", l_Weapon);
                        }
                        else if (InventoryManager::singleton.Get_Bank_Item_Count(l_Weapon) > 0)
                        {
                            const MapCoord bank_coord = InventoryManager::singleton.Get_Bank_Nearest_Coord(character);
                            if (character.Should_Move(bank_coord) == true)
                            {
                                character.Add_Move(sys, bank_coord);
                            }
                            else
                            {
                                character.Add_Withdraw_Item(sys, { l_Weapon, 1 });
                                character.Add_Equip_Item(sys, "weapon", l_Weapon);
                            }
                        }
                    }

                    if (character.Is_Empty() == true)
                    {
                        character.Add_Move(sys, *coord);
                        character.Add_Gathering(sys);
                    }
                }
            }
            else
            {
                throw std::runtime_error(fmt::format("can't gather '{}'", l_Monster_Name, item.code));
            }
        }

        if (t != nullptr)
        {
            const MapCoord* npc_coord = NPCManager::singleton.Get_Coords(t->npc.c_str());

            if (npc_coord != nullptr)
            {
                if (t->currency == TradeCurrency::Gold)
                {
                    const int l_Missing_Gold_Amount = t->amount - character.Get_Gold_Amount();

                    if (t->amount <= character.Get_Gold_Amount())
                    {
                        character.Add_Move(sys, *npc_coord);
                        character.Add_Buy_Item(sys, { item.code, 1 });
                    }
                    else if (l_Missing_Gold_Amount <= InventoryManager::singleton.Get_Gold_Amount())
                    {
                        const MapCoord coord = InventoryManager::singleton.Get_Bank_Nearest_Coord(character);
                        if (character.Should_Move(coord) == true)
                        {
                            character.Add_Move(sys, coord);
                        }
                        else
                        {
                            character.Add_Withdraw_Gold(sys, l_Missing_Gold_Amount);
                        }
                    }
                }
                else if (t->currency == TradeCurrency::TaskCoin)
                {
                    const int l_Missing_Task_Coin_Amount = t->amount - character.Get_Item_Count(Keywords::Items::Currency::tasks_coin);

                    if (l_Missing_Task_Coin_Amount <= 0)
                    {
                        character.Add_Move(sys, *npc_coord);
                        character.Add_Buy_Item(sys, { item.code, 1 });
                    }
                    else if (l_Missing_Task_Coin_Amount <
                             InventoryManager::singleton.Get_Bank_Item_Count(Keywords::Items::Currency::tasks_coin))
                    {
                        const MapCoord coord = InventoryManager::singleton.Get_Bank_Nearest_Coord(character);
                        if (character.Should_Move(coord) == true)
                        {
                            character.Add_Move(sys, coord);
                        }
                        else
                        {
                            character.Add_Withdraw_Item(sys, { Keywords::Items::Currency::tasks_coin, l_Missing_Task_Coin_Amount });
                        }
                    }
                }
            }
        }
    }
    else
    {
        for (const auto& i: r->required_items)
        {
            const int l_Item_Count = character.Get_Item_Count(i.code.c_str());
            if (l_Item_Count < i.quantity)
            {
                Get_Item(sys, character, { i.code, i.quantity });
                if (character.Is_Empty() == false)
                {
                    return;
                }
            }
        }
        if (character.Get_Item_Count(item.code.c_str()) < item.quantity)
        {
            character.Add_Move(sys, m_Workshop_Coords[r->skill_name]);
            character.Add_Craft(sys, { item.code, 1 });
        }
    }
}

ItemRequiredSkill ItemCraftingManager::Get_Required_Skill(const char* item_code) const
{
    const Recipe* r                = ItemManager::singleton.Get_Recipe(item_code);
    const GatheringRequirement* rg = ItemManager::singleton.Get_Gathering_Skill(item_code);
    ItemRequiredSkill requirements;
    if (r != nullptr)
    {
        requirements.requirements.emplace_back(std::make_pair(r->skill_name, r->skill_level));
        for (const auto& sub_item: r->required_items)
        {
            ItemRequiredSkill tmp = Get_Required_Skill(sub_item.code.c_str());
            requirements.requirements.insert(requirements.requirements.begin(), tmp.requirements.begin(), tmp.requirements.end());
        }
    }
    if (rg != nullptr)
    {
        requirements.requirements.emplace_back(std::make_pair(rg->skill_name, rg->skill_level));
    }
    return requirements;
}
