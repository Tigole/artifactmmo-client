#include "inventory_manager.hpp"

#include "character/character.hpp"
#include "item_manager.hpp"
#include "net/client.hpp"

InventoryManager InventoryManager::singleton;

void InventoryManager::Initialize(void)
{
    m_Resources_To_Deposit.push_back("sap");
    m_Resources_To_Deposit.push_back("apple");
    m_Resources_To_Deposit.push_back("sunflower");
    m_Resources_To_Deposit.push_back("algae");
    m_Resources_To_Deposit.push_back("gudgeon");
    m_Resources_To_Deposit.push_back("golden_egg");
    m_Resources_To_Deposit.push_back("fried_eggs");
    m_Resources_To_Deposit.push_back("emerald_stone");
    m_Resources_To_Deposit.push_back("sapphire_stone");
    m_Resources_To_Deposit.push_back("topaz_stone");
    m_Resources_To_Deposit.push_back("ruby_stone");
    m_Resources_To_Deposit.push_back("cooked_chicken");
    m_Resources_To_Deposit.push_back("cooked_gudgeon");
    m_Resources_To_Deposit.push_back("shell");
    m_Resources_To_Deposit.push_back("red_slimeball");
    m_Resources_To_Deposit.push_back("blue_slimeball");
    m_Resources_To_Deposit.push_back("green_slimeball");
    m_Resources_To_Deposit.push_back("yellow_slimeball");
    m_Resources_To_Deposit.push_back("feather");
    m_Resources_To_Deposit.push_back("egg");
    m_Resources_To_Deposit.push_back("raw_chicken");
    m_Resources_To_Deposit.push_back("tasks_coin");
    m_Resources_To_Deposit.push_back("ash_wood");
    m_Resources_To_Deposit.push_back("ash_plank");
    m_Resources_To_Deposit.push_back("copper_ore");
    m_Resources_To_Deposit.push_back("copper_bar");
    m_Resources_To_Deposit.push_back("iron_ore");
    m_Resources_To_Deposit.push_back("iron_bar");
    m_Resources_To_Deposit.push_back("raw_beef");
    m_Resources_To_Deposit.push_back("milk_bucket");
    m_Resources_To_Deposit.push_back("cowhide");

    Update_Cache();
}

void InventoryManager::Deposit_Resources(const System* sys, Character& character, const char* keep) const
{
    const MapCoord coord = Get_Bank_Nearest_Coord(character);
    if (character.Should_Move(coord))
    {
        character.Add_Move(sys, coord);
    }

    const int slot_count = character.Get_Inventory_Slot_Count();
    for (int ii = 0; ii < slot_count; ii++)
    {
        const ItemOrder item = character.Get_Inventory_Item(ii);

        if (item.quantity != 0)
        {
            character.Add_Deposit_Item(sys, item);
        }
    }

    character.Add_Deposit_Gold(sys, character.Get_Gold_Amount());
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
