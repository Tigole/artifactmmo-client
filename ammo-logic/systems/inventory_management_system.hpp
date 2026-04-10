#ifndef _INVENTORY_MANAGEMENT_SYSTEM_HPP
#define _INVENTORY_MANAGEMENT_SYSTEM_HPP 1

#include "system.hpp"

class InventoryManager;

class InventoryManagementSystem: public System
{
public:
    InventoryManagementSystem(InventoryManager& inventory_manager);

    void Fill_Pipeline(Character& character) override;

private:
    InventoryManager& m_Inventory_Manager;

    bool Has_Task_Item(Character& character);
};

#endif  // _INVENTORY_MANAGEMENT_SYSTEM_HPP
