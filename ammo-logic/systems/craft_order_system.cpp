#include "craft_order_system.hpp"

#include "managers/inventory_manager.hpp"
#include "managers/item_manager.hpp"

CraftOrderSystem::CraftOrderSystem(const char* system_name, ItemCraftingManager& item_crafting_manager, InventoryManager& bank) :
    System(system_name), m_Items(), m_Bank(bank), m_Item_Crafting_Manager(item_crafting_manager)
{}

void CraftOrderSystem::Fill_Pipeline(Character& character)
{
    for (const CraftOrder& l_Item: m_Items)
    {
        const int bank_amount = m_Bank.Get_Bank_Item_Count(l_Item.item_code);
        if ((bank_amount <= l_Item.threshold_amount) && (m_Item_Crafting_Manager.May_Craft(character, l_Item.item_code) == true))
        {
            const int l_Character_Item_Amount = character.Get_Item_Count(l_Item.item_code);
            if (character.Get_Inventory_Remaining_Space() > 10 && bank_amount < l_Item.target_amount)
            {
                printf("'%s' craft '%s' x%d (bank: %d target: %d min: %d)\n", character.Get_Character(), l_Item.item_code, 1, bank_amount,
                       l_Item.target_amount, l_Item.threshold_amount);
                m_Item_Crafting_Manager.Make_Craft_Item(this, character, { l_Item.item_code, 1 });
                return;
            }
            else
            {
                const MapCoord l_Bank_Coord = m_Bank.Get_Bank_Nearest_Coord(character);
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
