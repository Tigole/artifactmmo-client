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
        const CraftOrder order    = m_Items[ii];
        const Recipe* r           = ItemManager::singleton.Get_Recipe(order.item_code);
        const int bank_item_count = InventoryManager::singleton.Get_Bank_Item_Count(order.item_code);

        if (r == nullptr)
        {
            SYSTEM_PRINT("no recipe for '%s'", order.item_code);
            continue;
        }

        const int character_skill_level = character.Get_Skill_Level(r->skill_name.c_str());
        SYSTEM_PRINT("item '%s' required level: %d current level: %d", order.item_code, r->skill_level, character_skill_level);
        /// Do we have enough in bank ?
        if ((bank_item_count < order.target_amount) && (r->skill_level <= character_skill_level))
        {
            bool may_craft                         = true;
            int character_inventory_space_required = 0;
            int craft_count                        = 1;
            SYSTEM_PRINT("try to craft '%s'", order.item_code);

            for (std::size_t jj = 0; jj < r->required_items.size(); jj++)
            {
                const ItemOrder& sub_item     = r->required_items[jj];
                const int bank_sub_item_count = InventoryManager::singleton.Get_Bank_Item_Count(sub_item.code.c_str());
                character_inventory_space_required += sub_item.quantity;

                if (bank_sub_item_count < sub_item.quantity)
                {
                    may_craft = false;
                    SYSTEM_PRINT("missing '%s' x%d", sub_item.code.c_str(), sub_item.quantity);
                }
            }

            if (may_craft == false)
            {
                continue;
            }

            if (character.Get_Inventory_Remaining_Space() < character_inventory_space_required)
            {
                SYSTEM_PRINT("has to make space");
                character.Make_Clear_Inventory(this, nullptr);
                return;
            }

            if (character.Should_Move(bank_coord))
            {
                character.Add_Move(this, bank_coord);
                return;
            }

            if (r->required_items.size() == 1)
            {
                craft_count = character.Get_Inventory_Remaining_Space() / r->required_items[0].quantity;
                craft_count = std::min(craft_count, InventoryManager::singleton.Get_Bank_Item_Count(r->required_items[0].code.c_str()) /
                                                        r->required_items[0].quantity);
                SYSTEM_PRINT(
                    "1 required item (character.Get_Inventory_Remaining_Space(): %d r->required_items[0].quantity: %d "
                    "InventoryManager::singleton.Get_Bank_Item_Count(r->required_items[0].code.c_str()): %d craft_count: %d)",
                    character.Get_Inventory_Remaining_Space(), r->required_items[0].quantity,
                    InventoryManager::singleton.Get_Bank_Item_Count(r->required_items[0].code.c_str()), craft_count);
            }

            SYSTEM_PRINT("craft_count: %d order.target_amount: %d bank_item_count: %d order.target_amount - bank_item_count: %d",
                         craft_count, order.target_amount, bank_item_count, order.target_amount - bank_item_count);
            craft_count = std::min(craft_count, order.target_amount - bank_item_count);

            SYSTEM_PRINT("will craft '%s' x%d", order.item_code, craft_count);

            for (std::size_t jj = 0; jj < r->required_items.size(); jj++)
            {
                const ItemOrder& sub_item = r->required_items[jj];

                character.Add_Withdraw_Item(this, { sub_item.code, sub_item.quantity * craft_count });
            }

            const ItemOrder craft_order = { order.item_code, craft_count };
            character.Add_Move(this, m_Workshop_Coord);
            character.Add_Craft(this, craft_order);
            character.Add_Move(this, InventoryManager::singleton.Get_Bank_Nearest_Coord(m_Workshop_Coord));
            character.Make_Clear_Inventory(this, nullptr);
            return;
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
        return;
    }

    if (bank_item_count < 5)
    {
        if (InventoryManager::singleton.Get_Bank_Item_Count(task_coin) < 8)
        {
            SYSTEM_PRINT("Not enough '%s'", task_coin);
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
