#include "inventory_manager.hpp"

#include "character/character.hpp"
#include "item_manager.hpp"
#include "net/client.hpp"

InventoryManager InventoryManager::singleton;

void InventoryManager::Initialize(void)
{
    Update_Cache();
}

int InventoryManager::Get_Bank_Item_Count(const char* item_code)
{
    auto it = m_Bank_Content.find(item_code);
    if (it != m_Bank_Content.end())
    {
        return it->second;
    }
    return 0;
}

int InventoryManager::Get_Gold_Amount(void)
{
    return m_Gold_Amount;
}

MapCoord InventoryManager::Get_Bank_Nearest_Coord(Character& character) const
{
    return Get_Bank_Nearest_Coord(character.Get_Map_Coord());
}

MapCoord InventoryManager::Get_Bank_Nearest_Coord(MapCoord coord) const
{
    const int dist_bank_1 = coord.Get_Distance(m_Bank_Coord_1);
    const int dist_bank_2 = coord.Get_Distance(m_Bank_Coord_2);
    if (dist_bank_1 < dist_bank_2)
    {
        return m_Bank_Coord_1;
    }
    return m_Bank_Coord_2;
}

void InventoryManager::Get_Fight_Items(int level, std::vector<InventoryWeapons>& weapons, std::vector<InventoryArmorPart>& helmets,
                                       std::vector<InventoryArmorPart>& body_armors, std::vector<InventoryArmorPart>& leg_armors,
                                       std::vector<InventoryArmorPart>& boots, std::vector<InventoryArmorPart>& shields,
                                       std::vector<InventoryArmorPart>& rings1, std::vector<InventoryArmorPart>& rings2,
                                       std::vector<InventoryArmorPart>& amulets) const
{
    auto armor_handler = [this](int level, const char* armor_type, const char* item_code, std::vector<InventoryArmorPart>& armors)
    {
        if (ItemManager::singleton.Is_Type(item_code, armor_type) && (ItemManager::singleton.Get_Item_Level(item_code) <= level))
        {
            armors.push_back({ item_code, ItemManager::singleton.Get_Armor_Resistance(item_code),
                               ItemManager::singleton.Get_Armor_Damage(item_code), ItemManager::singleton.Get_Armor_Hp(item_code),
                               ItemManager::singleton.Get_Item_Level(item_code) });
        }
    };
    for (const auto& item: m_Bank_Content)
    {
        const char* item_code = item.first.c_str();
        if (ItemManager::singleton.Is_Type(item_code, "weapon") && (ItemManager::singleton.Get_Item_Level(item_code) <= level))
        {
            weapons.emplace_back(item_code, ItemManager::singleton.Get_Weapon_Attack(item_code),
                                 std::array<int, 4> {
                                     { 0, 0, 0, 0 }
            },
                                 ItemManager::singleton.Get_Item_Level(item_code));
        }
        armor_handler(level, "helmet", item_code, helmets);
        armor_handler(level, "body_armor", item_code, body_armors);
        armor_handler(level, "leg_armor", item_code, leg_armors);
        armor_handler(level, "boots", item_code, boots);
        armor_handler(level, "amulet", item_code, amulets);
        armor_handler(level, "ring", item_code, rings1);
        // armor_handler(level, "ring", item_code, rings2);
        armor_handler(level, "shield", item_code, shields);
    }
}

void InventoryManager::Update_Cache(void)
{
    nlohmann::json tmp;
    Client::singleton.mt_Get_Bank_Items(tmp);

    m_Bank_Content.clear();
    for (auto& d: tmp["data"])
    {
        m_Bank_Content.emplace(d["code"], d["quantity"].get<int>());
    }

    Client::singleton.Get_Bank_Detail(tmp);

    m_Gold_Amount = tmp["data"]["gold"].get<int>();
}
