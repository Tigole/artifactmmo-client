#ifndef _CRAFT_ORDER_SYSTEM_HPP
#define _CRAFT_ORDER_SYSTEM_HPP 1

#include "system.hpp"

class ItemCraftingManager;
class InventoryManager;

struct CraftOrder
{
    const char* item_code;
    int threshold_amount;
    int target_amount;
};

class CraftOrderSystem: public System
{
public:
    CraftOrderSystem(const char* system_name, ItemCraftingManager& item_crafting_manager, InventoryManager& bank) :
        System(system_name), m_Items(), m_Bank(bank), m_Item_Crafting_Manager(item_crafting_manager)
    {}

    virtual ~CraftOrderSystem() = default;

    void Fill_Pipeline(Character& character) override
    {
        if (character.Is_Task_Item())
        {
            // return;
        }
        if (character.Is_Task_Monster())
        {
            /// If MayWin so return;
            // return;
        }
        for (const CraftOrder& l_Item: m_Items)
        {
            if ((m_Bank.Get_Bank_Item_Count(l_Item.item_code) <= l_Item.threshold_amount) &&
                (m_Item_Crafting_Manager.May_Craft(character, l_Item.item_code) == true))
            {
                const int l_Character_Item_Amount = character.Get_Item_Count(l_Item.item_code);
                if (l_Character_Item_Amount < l_Item.target_amount)
                {
                    m_Item_Crafting_Manager.Make_Craft_Item(character, { l_Item.item_code, 1 });
                    return;
                }
                else
                {
                    const MapCoord l_Bank_Coord = m_Bank.Get_Bank_Nearest_Coord(character);
                    if (character.Should_Move(l_Bank_Coord) == true)
                    {
                        character.Add_Move(l_Bank_Coord);
                        return;
                    }
                    else
                    {
                        character.Add_Deposit_Item({ l_Item.item_code, l_Item.target_amount });
                        return;
                    }
                }
            }
        }
    }

protected:
    std::vector<CraftOrder> m_Items;

private:
    InventoryManager& m_Bank;
    ItemCraftingManager& m_Item_Crafting_Manager;
};

#endif  // _CRAFT_ORDER_SYSTEM_HPP
