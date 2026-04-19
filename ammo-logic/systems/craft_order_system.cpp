#include "craft_order_system.hpp"

#include "keywords.hpp"
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
    m_Items.push_back({ Keywords::Items::Weapons::Tools::Axes::voidstone_axe, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::Pickaxes::voidstone_pickaxe, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::Gloves::voidstone_gloves, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::FishingRods::voidstone_fishing_rod, target_amount });

    m_Items.push_back({ Keywords::Items::Weapons::Tools::Axes::adamantite_axe, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::Pickaxes::adamantite_pickaxe, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::Gloves::adamantite_gloves, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::FishingRods::adamantite_fishing_rod, target_amount });

    m_Items.push_back({ Keywords::Items::Weapons::Tools::Axes::mithril_axe, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::Pickaxes::mithril_pickaxe, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::Gloves::mithril_gloves, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::FishingRods::mithril_fishing_rod, target_amount });

    m_Items.push_back({ Keywords::Items::Weapons::Tools::Axes::gold_axe, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::Pickaxes::gold_pickaxe, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::Gloves::golden_gloves, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::FishingRods::gold_fishing_rod, target_amount });

    m_Items.push_back({ Keywords::Items::Weapons::Tools::Axes::steel_axe, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::Pickaxes::steel_pickaxe, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::Gloves::steel_gloves, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::FishingRods::steel_fishing_rod, target_amount });

    m_Items.push_back({ Keywords::Items::Weapons::Tools::Axes::iron_axe, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::Pickaxes::iron_pickaxe, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::Gloves::leather_gloves, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::FishingRods::spruce_fishing_rod, target_amount });

    m_Items.push_back({ Keywords::Items::Weapons::Tools::Axes::copper_axe, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::Pickaxes::copper_pickaxe, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::Gloves::apprentice_gloves, target_amount });
    m_Items.push_back({ Keywords::Items::Weapons::Tools::FishingRods::fishing_net, target_amount });

    m_Workshop_Coord = { 2, 1 };
}

WeaponCraftSystem WeaponCraftSystem::singleton;

WeaponCraftSystem::WeaponCraftSystem() : CraftOrderSystem("WeaponCraftSystem")
{
    m_Items.push_back({ Keywords::Items::Weapons::iron_sword, 1 });
    m_Items.push_back({ Keywords::Items::Weapons::fire_staff, 1 });
    m_Items.push_back({ Keywords::Items::Weapons::water_bow, 1 });
    m_Items.push_back({ Keywords::Items::Weapons::sticky_sword, 1 });
    m_Items.push_back({ Keywords::Items::Weapons::wooden_staff, 1 });
    m_Items.push_back({ Keywords::Items::Weapons::sticky_dagger, 1 });
    m_Items.push_back({ Keywords::Items::Weapons::copper_dagger, 1 });

    m_Workshop_Coord = { 2, 1 };
}

AlchemyCraftingSystem AlchemyCraftingSystem::singleton;

AlchemyCraftingSystem::AlchemyCraftingSystem() : CraftOrderSystem("AlchemyCraftingSystem")
{
    m_Items.push_back({ Keywords::Items::Utilities::enchanted_health_potion, 50 });
    m_Items.push_back({ Keywords::Items::Utilities::greater_health_potion, 50 });
    m_Items.push_back({ Keywords::Items::Utilities::health_boost_potion, 50 });
    m_Items.push_back({ Keywords::Items::Utilities::health_splash_potion, 50 });
    m_Items.push_back({ Keywords::Items::Utilities::health_potion, 50 });
    m_Items.push_back({ Keywords::Items::Utilities::minor_health_potion, 50 });
    m_Items.push_back({ Keywords::Items::Utilities::small_health_potion, 50 });

    m_Workshop_Coord = { 2, 3 };
}

CookingSystem CookingSystem::singleton;

CookingSystem::CookingSystem() : CraftOrderSystem("CookingSystem")
{
    m_Items.push_back({ Keywords::Items::Consumables::Food::cooked_shrimp, 50 });
    m_Items.push_back({ Keywords::Items::Consumables::Food::cooked_beef, 50 });
    m_Items.push_back({ Keywords::Items::Consumables::Food::cooked_gudgeon, 300 });
    m_Items.push_back({ Keywords::Items::Consumables::Food::fried_eggs, 10 });
    m_Items.push_back({ Keywords::Items::Consumables::Food::cooked_chicken, 50 });

    m_Workshop_Coord = { 1, 1 };
}

MiningCraftingSystem MiningCraftingSystem::singleton;

MiningCraftingSystem::MiningCraftingSystem() : CraftOrderSystem("MiningCraftingSystem")
{
    constexpr const int target_amout = 50;
    m_Items.push_back({ Keywords::Items::Resources::Bar::adamantite_bar, target_amout });
    m_Items.push_back({ Keywords::Items::Resources::Bar::mithril_bar, target_amout });
    m_Items.push_back({ Keywords::Items::Resources::Bar::strangold_bar, target_amout });
    m_Items.push_back({ Keywords::Items::Resources::Bar::gold_bar, target_amout });
    m_Items.push_back({ Keywords::Items::Resources::Bar::steel_bar, target_amout });
    m_Items.push_back({ Keywords::Items::Resources::Bar::iron_bar, target_amout });
    m_Items.push_back({ Keywords::Items::Resources::Bar::copper_bar, target_amout });

    m_Workshop_Coord = { 1, 5 };
}

WoodcuttingCraftingSystem WoodcuttingCraftingSystem::singleton;

WoodcuttingCraftingSystem::WoodcuttingCraftingSystem() : CraftOrderSystem("WoodcuttingCraftingSystem")
{
    constexpr const int target_amout = 50;
    m_Items.push_back({ Keywords::Items::Resources::Plank::maple_plank, target_amout });
    m_Items.push_back({ Keywords::Items::Resources::Plank::magical_plank, target_amout });
    m_Items.push_back({ Keywords::Items::Resources::Plank::dead_wood_plank, target_amout });
    m_Items.push_back({ Keywords::Items::Resources::Plank::palm_plank, target_amout });
    m_Items.push_back({ Keywords::Items::Resources::Plank::hardwood_plank, target_amout });
    m_Items.push_back({ Keywords::Items::Resources::Plank::spruce_plank, target_amout });
    m_Items.push_back({ Keywords::Items::Resources::Plank::ash_plank, target_amout });

    m_Workshop_Coord = { -2, -3 };
}

GearcraftingSystem GearcraftingSystem::singleton;

GearcraftingSystem::GearcraftingSystem() : CraftOrderSystem("GearcraftingSystem")
{
    constexpr const int target_amout = 1;
    m_Items.push_back({ Keywords::Items::Helmets::copper_helmet, target_amout });
    m_Items.push_back({ Keywords::Items::Boots::copper_boots, target_amout });
    m_Items.push_back({ Keywords::Items::LegArmors::copper_legs_armor, target_amout });
    m_Items.push_back({ Keywords::Items::Shields::wooden_shield, target_amout });
    m_Items.push_back({ Keywords::Items::BodyArmors::feather_coat, target_amout });
    m_Items.push_back({ Keywords::Items::Amulets::life_amulet, target_amout });
    m_Items.push_back({ Keywords::Items::Boots::leather_boots, target_amout });
    m_Items.push_back({ Keywords::Items::BodyArmors::leather_armor, target_amout });
    m_Items.push_back({ Keywords::Items::Helmets::adventurer_helmet, target_amout });
    m_Items.push_back({ Keywords::Items::LegArmors::iron_legs_armor, target_amout });
    m_Items.push_back({ Keywords::Items::BodyArmors::iron_armor, target_amout });
    m_Items.push_back({ Keywords::Items::BodyArmors::adventurer_vest, target_amout });
    m_Items.push_back({ Keywords::Items::Helmets::leather_hat, target_amout });
    m_Items.push_back({ Keywords::Items::LegArmors::leather_legs_armor, target_amout });

    m_Workshop_Coord = { 3, 1 };
}

BuyingSystem BuyingSystem::singleton;

BuyingSystem::BuyingSystem() : System("BuyingSystem") {}

void BuyingSystem::Fill_Pipeline(Character& character)
{
    const char* item_to_buy           = Keywords::Items::Resources::Task::jasper_crystal;
    const char* task_coin             = Keywords::Items::Currency::tasks_coin;
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
