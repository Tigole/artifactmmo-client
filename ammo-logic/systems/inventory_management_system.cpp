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
            if (task_item_count != 0)
            {
                InventoryManager::singleton.Deposit_Resources(this, character, character.Get_Task().c_str());
            }
        }
        else
        {
            InventoryManager::singleton.Deposit_Resources(this, character, character.Get_Task().c_str());
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
