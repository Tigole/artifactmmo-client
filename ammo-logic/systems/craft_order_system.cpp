#include "craft_order_system.hpp"

#include "managers/achievement_manager.hpp"
#include "managers/inventory_manager.hpp"
#include "managers/item_manager.hpp"

CraftOrderSystem::CraftOrderSystem(const char* system_name) : System(system_name), m_Items() {}

void CraftOrderSystem::Fill_Pipeline(Character& character)
{
    const MapCoord bank_coord = InventoryManager::singleton.Get_Bank_Nearest_Coord(character);

    for (std::size_t ii = 0; ii < m_Items.size(); ii++)
    {
        const CraftOrder order = m_Items[ii];

        if (Make_Craft(character, m_Workshop_Coord, order.item_code, order.target_amount) != 0)
        {
            break;
        }
    }
}

ToolCraftSystem ToolCraftSystem::singleton;

ToolCraftSystem::ToolCraftSystem() : CraftOrderSystem("ToolCraftSystem")
{
    constexpr const int target_amount = 1;
    m_Items.push_back({ "voidstone_axe", target_amount });
    m_Items.push_back({ "voidstone_pickaxe", target_amount });
    m_Items.push_back({ "voidstone_gloves", target_amount });
    m_Items.push_back({ "voidstone_fishing_rod", target_amount });

    m_Items.push_back({ "adamantite_axe", target_amount });
    m_Items.push_back({ "adamantite_pickaxe", target_amount });
    m_Items.push_back({ "adamantite_gloves", target_amount });
    m_Items.push_back({ "adamantite_fishing_rod", target_amount });

    m_Items.push_back({ "mithril_axe", target_amount });
    m_Items.push_back({ "mithril_pickaxe", target_amount });
    m_Items.push_back({ "mithril_gloves", target_amount });
    m_Items.push_back({ "mithril_fishing_rod", target_amount });

    m_Items.push_back({ "gold_axe", target_amount });
    m_Items.push_back({ "gold_pickaxe", target_amount });
    m_Items.push_back({ "golden_gloves", target_amount });
    m_Items.push_back({ "gold_fishing_rod", target_amount });

    m_Items.push_back({ "steel_axe", target_amount });
    m_Items.push_back({ "steel_pickaxe", target_amount });
    m_Items.push_back({ "steel_gloves", target_amount });
    m_Items.push_back({ "steel_fishing_rod", target_amount });

    m_Items.push_back({ "iron_axe", target_amount });
    m_Items.push_back({ "iron_pickaxe", target_amount });
    m_Items.push_back({ "leather_gloves", target_amount });
    m_Items.push_back({ "spruce_fishing_rod", target_amount });

    m_Items.push_back({ "copper_axe", target_amount });
    m_Items.push_back({ "copper_pickaxe", target_amount });
    m_Items.push_back({ "apprentice_gloves", target_amount });
    m_Items.push_back({ "fishing_net", target_amount });

    m_Workshop_Coord = { 2, 1 };
}

WeaponCraftSystem WeaponCraftSystem::singleton;

WeaponCraftSystem::WeaponCraftSystem() : CraftOrderSystem("WeaponCraftSystem")
{
    m_Items.push_back({ "iron_sword", 1 });
    m_Items.push_back({ "fire_staff", 1 });
    m_Items.push_back({ "water_bow", 1 });
    m_Items.push_back({ "sticky_sword", 1 });
    m_Items.push_back({ "wooden_staff", 1 });
    m_Items.push_back({ "sticky_dagger", 1 });
    m_Items.push_back({ "copper_dagger", 1 });

    m_Workshop_Coord = { 2, 1 };
}

AlchemyCraftingSystem AlchemyCraftingSystem::singleton;

AlchemyCraftingSystem::AlchemyCraftingSystem() : CraftOrderSystem("AlchemyCraftingSystem")
{
    m_Items.push_back({ "enchanted_health_potion", 50 });
    m_Items.push_back({ "greater_health_potion", 50 });
    m_Items.push_back({ "health_boost_potion", 50 });
    m_Items.push_back({ "health_splash_potion", 50 });
    m_Items.push_back({ "health_potion", 50 });
    m_Items.push_back({ "minor_health_potion", 50 });
    m_Items.push_back({ "small_health_potion", 50 });

    m_Workshop_Coord = { 2, 3 };
}

CookingSystem CookingSystem::singleton;

CookingSystem::CookingSystem() : CraftOrderSystem("CookingSystem")
{
    m_Items.push_back({ "cooked_shrimp", 50 });
    m_Items.push_back({ "cooked_beef", 50 });
    m_Items.push_back({ "cooked_gudgeon", 300 });
    m_Items.push_back({ "fried_eggs", 10 });
    m_Items.push_back({ "cooked_chicken", 50 });

    m_Workshop_Coord = { 1, 1 };
}

MiningCraftingSystem MiningCraftingSystem::singleton;

MiningCraftingSystem::MiningCraftingSystem() : CraftOrderSystem("MiningCraftingSystem")
{
    constexpr const int target_amout = 50;
    m_Items.push_back({ "adamantine_bar", target_amout });
    m_Items.push_back({ "mithril_bar", target_amout });
    m_Items.push_back({ "strangold_bar", target_amout });
    m_Items.push_back({ "gold_bar", target_amout });
    m_Items.push_back({ "steal_bar", target_amout });
    m_Items.push_back({ "iron_bar", target_amout });
    m_Items.push_back({ "copper_bar", target_amout });

    m_Workshop_Coord = { 1, 5 };
}

WoodcuttingCraftingSystem WoodcuttingCraftingSystem::singleton;

WoodcuttingCraftingSystem::WoodcuttingCraftingSystem() : CraftOrderSystem("WoodcuttingCraftingSystem")
{
    constexpr const int target_amout = 50;
    m_Items.push_back({ "maple_plank", target_amout });
    m_Items.push_back({ "magical_plank", target_amout });
    m_Items.push_back({ "dead_wood_plank", target_amout });
    m_Items.push_back({ "palm_plank", target_amout });
    m_Items.push_back({ "hardwood_plank", target_amout });
    m_Items.push_back({ "birch_plank", target_amout });
    m_Items.push_back({ "spruce_plank", target_amout });
    m_Items.push_back({ "ash_plank", target_amout });

    m_Workshop_Coord = { -2, -3 };
}

GearcraftingSystem GearcraftingSystem::singleton;

GearcraftingSystem::GearcraftingSystem() : CraftOrderSystem("GearcraftingSystem")
{
    constexpr const int target_amout = 1;
    m_Items.push_back({ "copper_helmet", target_amout });
    m_Items.push_back({ "copper_boots", target_amout });
    m_Items.push_back({ "copper_legs_armor", target_amout });
    m_Items.push_back({ "wooden_shield", target_amout });
    m_Items.push_back({ "feather_coat", target_amout });
    m_Items.push_back({ "life_amulet", target_amout });
    m_Items.push_back({ "leather_boots", target_amout });
    m_Items.push_back({ "leather_armor", target_amout });
    m_Items.push_back({ "adventurer_helmet", target_amout });
    m_Items.push_back({ "iron_legs_armor", target_amout });
    m_Items.push_back({ "iron_armor", target_amout });
    m_Items.push_back({ "adventurer_vest", target_amout });
    m_Items.push_back({ "leather_hat", target_amout });
    m_Items.push_back({ "leather_legs_armor", target_amout });

    m_Workshop_Coord = { 3, 1 };
}

BuyingSystem BuyingSystem::singleton;

BuyingSystem::BuyingSystem() : System("BuyingSystem") {}

void BuyingSystem::Fill_Pipeline(Character& character)
{
    const char* item_to_buy           = "jasper_crystal";
    const char* task_coin             = "tasks_coin";
    const int bank_item_count         = InventoryManager::singleton.Get_Bank_Item_Count(item_to_buy);
    const MapCoord trader_coord       = { 5, 11 };
    const MapCoord nearest_bank_coord = InventoryManager::singleton.Get_Bank_Nearest_Coord(character);

    if (AchivementManager::singleton.Is_Completed("tasks_farmer") == false)
    {
        SYSTEM_PRINT("achievement not completed");
        return;
    }

    if (bank_item_count < 5)
    {
        if (InventoryManager::singleton.Get_Bank_Item_Count(task_coin) < 8)
        {
            SYSTEM_PRINT("not enough '%s'", task_coin);
            return;
        }

        /// Move to bank
        if (character.Should_Move(nearest_bank_coord))
        {
            character.Add_Move(this, nearest_bank_coord);
            return;
        }

        character.Add_Withdraw_Item(this, { task_coin, 8 });
        character.Add_Move(this, trader_coord);
        character.Add_Buy_Item(this, { item_to_buy, 1 });
        character.Add_Move(this, InventoryManager::singleton.Get_Bank_Nearest_Coord(trader_coord));
        character.Make_Clear_Inventory(this, nullptr);
    }
}
