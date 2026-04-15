#include "craft_order_system.hpp"

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
            SYSTEM_PRINT("no recipe for '%s'\n", order.item_code);
            continue;
        }

        const int character_skill_level = character.Get_Skill_Level(r->skill_name.c_str());
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
                InventoryManager::singleton.Deposit_Resources(this, character, nullptr);
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
            }

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
            character.Add_Deposit_Item(this, craft_order);
            return;
        }
    }
#if 0
    for (const CraftOrder& l_Item: m_Items)
    {
        const int bank_amount = InventoryManager::singleton.Get_Bank_Item_Count(l_Item.item_code);
        if ((bank_amount <= l_Item.threshold_amount) && (ItemCraftingManager::singleton.May_Craft(character, l_Item.item_code) == true))
        {
            const int l_Character_Item_Amount = character.Get_Item_Count(l_Item.item_code);
            if (character.Get_Inventory_Remaining_Space() > 10 && bank_amount < l_Item.target_amount)
            {
                printf("'%s' craft '%s' x%d (bank: %d target: %d min: %d)\n", character.Get_Character(), l_Item.item_code, 1, bank_amount,
                       l_Item.target_amount, l_Item.threshold_amount);
                ItemCraftingManager::singleton.Make_Craft_Item(this, character, { l_Item.item_code, 1 });
                return;
            }
            else
            {
                const MapCoord l_Bank_Coord = InventoryManager::singleton.Get_Bank_Nearest_Coord(character);
                if (character.Should_Move(l_Bank_Coord) == true)
                {
                    character.Add_Move(this, l_Bank_Coord);
                    return;
                }
                else
                {
                    if (l_Character_Item_Amount > 0)
                    {
                        character.Add_Deposit_Item(this, { l_Item.item_code, l_Character_Item_Amount });
                    }
                    return;
                }
            }
        }
    }
#endif
}

ToolCraftSystem::ToolCraftSystem() : CraftOrderSystem("ToolCraftSystem")
{
    constexpr const int target_amount = 5;
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

AlchemyCraftingSystem AlchemyCraftingSystem::singleton;
CookingSystem CookingSystem::singleton;
MiningCraftingSystem MiningCraftingSystem::singleton;
WoodcuttingCraftingSystem WoodcuttingCraftingSystem::singleton;
ToolCraftSystem ToolCraftSystem::singleton;
GearcraftingSystem GearcraftingSystem::singleton;
