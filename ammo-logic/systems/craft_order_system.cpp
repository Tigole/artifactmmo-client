#include "craft_order_system.hpp"

#include "managers/inventory_manager.hpp"
#include "managers/item_manager.hpp"

CraftOrderSystem::CraftOrderSystem(const char* system_name) : System(system_name), m_Items() {}

void CraftOrderSystem::Fill_Pipeline(Character& character)
{
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
}

AlchemyCraftingSystem AlchemyCraftingSystem::singleton;
CookingSystem CookingSystem::singleton;
MiningCraftingSystem MiningCraftingSystem::singleton;
WoodcuttingCraftingSystem WoodcuttingCraftingSystem::singleton;
ToolCraftSystem ToolCraftSystem::singleton;
GearcraftingSystem GearcraftingSystem::singleton;
