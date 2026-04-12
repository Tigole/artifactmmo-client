#include "inventory_management_system.hpp"

#include "managers/inventory_manager.hpp"

InventoryManagementSystem::InventoryManagementSystem(InventoryManager& inventory_manager) :
    System("InventoryManagementSystem"), m_Inventory_Manager(inventory_manager)
{}

void InventoryManagementSystem::Fill_Pipeline(Character& character)
{
    const int l_Remaining_Space      = character.Get_Inventory_Remaining_Space();
    const int l_Remaining_Spot_Count = character.Get_Inventory_Remaining_Slot_Count();

    if (l_Remaining_Space == 0 || l_Remaining_Spot_Count == 0)
    {
        if (character.Is_Task_Item() == true)
        {
            //
        }
        else
        {
            m_Inventory_Manager.Deposit_Resources(this, character, character.Get_Task().c_str());
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
