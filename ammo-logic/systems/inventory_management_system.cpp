#include "inventory_management_system.hpp"

#include "managers/inventory_manager.hpp"

InventoryManagementSystem InventoryManagementSystem::singleton;

InventoryManagementSystem::InventoryManagementSystem() : System("InventoryManagementSystem") {}

void InventoryManagementSystem::Fill_Pipeline(Character& character)
{
    const int l_Remaining_Space      = character.Get_Inventory_Remaining_Space();
    const int l_Remaining_Spot_Count = character.Get_Inventory_Remaining_Slot_Count();

    if (l_Remaining_Space == 0 || l_Remaining_Spot_Count == 0)
    {
        if (character.Is_Task_Item() == true)
        {
            const int task_item_count = character.Get_Item_Count(character.Get_Task().c_str());
            if (task_item_count == 0)
            {
                character.Make_Clear_Inventory(this, character.Get_Task().c_str());
                return;
            }
        }
        else
        {
            character.Make_Clear_Inventory(this, nullptr);
            return;
        }
    }

    if (character.Should_Move(InventoryManager::singleton.Get_Bank_Nearest_Coord(character.Get_Map_Coord())) == false)
    {
        if (InventoryManager::singleton.Get_Bank_Remaining_Slot_Count() < 5)
        {
            const int gold_amount    = InventoryManager::singleton.Get_Gold_Amount();
            const int expansion_cost = InventoryManager::singleton.Get_Bank_Expansion_Cost();
            SYSTEM_PRINT("may buy expansion");
            if (gold_amount < expansion_cost)
            {
                SYSTEM_PRINT("not enough money (required: %d current: %d)", gold_amount, expansion_cost);
            }
            else
            {
                SYSTEM_PRINT("will buy expansion for %d", expansion_cost);
                character.Add_Withdraw_Gold(this, expansion_cost);
                character.Add_Buy_Bank_Expasion(this);
            }
        }
    }
}

bool InventoryManagementSystem::Has_Task_Item(Character& character)
{
    const int l_Slot_Count = character.Get_Inventory_Slot_Count();
    for (int ii = 0; ii < l_Slot_Count; ii++)
    {
        if ((character.Get_Inventory_Item(ii).code.size()) && (character.Get_Inventory_Item(ii).code == character.Get_Task()))
        {
            return true;
        }
    }
    return false;
}
